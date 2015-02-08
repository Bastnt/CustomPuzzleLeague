#include "physic_engine.h"
#include "board.h"
#include <set>
#include <utility>
#include "2d\CCActionInterval.h"

void PhysicEngine::Step() {

	// Combo blocks
	std::set<std::pair<uint32_t, uint32_t> > combo_list;

	// Increments counters
	// Creep check
	if (creep_step_ >= config_.creep_division_steps) {
		creep_step_ = 0;
		if (generate_newline_move_ >= config_.block_division) {
			generate_newline_move_ = 0;
			// generate a line
			parent_board_.AddLine();
			// move cursor in consequence
			parent_board_.MoveCursor(Board::Direction::UP);
			parent_board_.ResetPosition();
		}
		else {
			++generate_newline_move_;
			parent_board_.MoveUp();
		}
	}
	else {
		++creep_step_;
	}

	uint32_t i, j;
	for (i = config_.ground_height; i < config_.height; ++i) {
		for (j = 0; j < config_.width; ++j) {
			auto& block = squares_[i][j];

			if (!block->IsBlock())
				continue;

			// IDLE -> HANGING?
			if (i > config_.ground_height && block->state == Block::State::IDLE) {
				auto& block_below = squares_[i - 1][j];
				if (!block_below->IsGround()) {
					block->state = Block::State::HANGING;
					block->progression = 0.f;
				}
			}
			// HANGING -> FALL?
			if (block->state == Block::State::HANGING) {
				++block->progression;
				if (block->progression > config_.hanging_time) {
					block->state = Block::State::FALLING;
					block->progression = 0.f;
				}
			}

			// FALL -> IDLE?
			if (block->state == Block::State::FALLING) {
				++block->progression;
				if (i == config_.ground_height) {
					block->state = Block::State::IDLE;
					return;
				}
				else if (squares_[i - 1][j]->IsGround()) {
					block->state = Block::State::IDLE;
				}

				// FALL -> FALL?
				else if (block->progression >= config_.falling_time) {
					auto& block_below = squares_[i - 1][j];
					block->state = Block::State::FALLING;
					block->progression = 0.f;
					if (!block_below->IsBlock()) {
						block->view->setPositionY((i - 1) * config_.block_size);
						std::swap(block, block_below);
					}
				}
			}

			if (block->state == Block::State::IDLE) {
				// IDLE -> DYING?
				int32_t left_check, right_check;
				for (left_check = j - 1; left_check >= 0; --left_check) {
					auto& b = squares_[i][left_check];
					if (!b->IsBlock() || b->state != Block::State::IDLE || b->color != block->color)
						break;
				}
				for (right_check = j + 1; right_check < config_.width; ++right_check) {
					auto& b = squares_[i][right_check];
					if (!b->IsBlock() || b->state != Block::State::IDLE || b->color != block->color)
						break;
				}

				int32_t up_check, bottom_check;
				for (bottom_check = i - 1; bottom_check >= config_.ground_height; --bottom_check) {
					auto& b = squares_[bottom_check][j];
					if (!b->IsBlock() || b->color != block->color)
						break;
				}
				for (up_check = i + 1; up_check < config_.width; ++up_check) {
					auto& b = squares_[up_check][j];
					if (!b->IsBlock() || b->color != block->color)
						break;
				}
				// Horizontal dying blocks
				if (right_check - left_check > 3)
					for (uint32_t a = left_check + 1; a < right_check; ++a)
						combo_list.insert(std::make_pair(i, a));

				// Vertical dying blocks
				if (up_check - bottom_check > 3)
					for (uint32_t a = bottom_check + 1; a < up_check; ++a)
						combo_list.insert(std::make_pair(a, j));

			}

			// DYING -> EMPTY?
			if (block->state == Block::State::DYING) {
				++block->progression;
				if (block->progression > config_.dying_time) {
					block = std::make_unique<Empty>();
				}
			}
		}
	}

	// Process die list
	for (auto& coord : combo_list) {
		auto& b = squares_[coord.first][coord.second];
		b->state = Block::State::DYING;
		b->view->setColor({ 150, 75, 0 });
		b->view->runAction(cocos2d::Blink::create(config_.dying_time * config_.time_step / 1.5f, 15));
		b->progression = 0.f;
	}
}