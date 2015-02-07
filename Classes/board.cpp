#include <algorithm>

#include "2d/CCSprite.h"
#include "2d\CCActionInterval.h"
#include "2d\CCActionInstant.h"

#include "board.h"
#include "random_generator.h"

USING_NS_CC;

Block::Block(Node* parent_view, float width, uint8_t color) : Square(color) {
	state = Block::State::IDLE;
	view = Sprite::create(std::to_string(color)+".png");
	auto size = view->getContentSize();
	view->setScale(width / size.width, width / size.height);
	view->getTexture()->setAliasTexParameters();
	view->setAnchorPoint({ 0.f, 0.f });
	parent_view->addChild(view);
}

Block::~Block() {
	view->removeFromParentAndCleanup(true);
}

void Board::PositionViews() {
	float i = 0.f, j = 0.f;
	for (auto& line : squares) {
		i = 0;
		for (auto& square : line) {
			if (square->IsBlock()) {
				square->view->setPosition({ i, j });
			}
			i += block_size_;
		}
		j += block_size_;
	}
}

void Board::AddLine(Fill filling) {
	squares.push_front(std::vector<std::unique_ptr<Square> >(config.width));
	squares.pop_back();

	if (filling == Fill::RANDOMLY) {
		auto maximum = config.max_color - 1;
		for (auto& s : squares.front()) {
			s = std::make_unique<Block>(this, block_size_, static_cast<uint8_t>(RandomGenerator::instance.Rand(0, maximum)));
		}
	}

	PositionViews();
}

void Board::MoveCursor(Board::Direction d) {
	switch (d) {
	case Board::Direction::UP:
		if (cursor_pos_.y < config.height - 1)
			++cursor_pos_.y;
		break;
	case Board::Direction::RIGHT:
		if (cursor_pos_.x < config.width - 2)
			++cursor_pos_.x;
		break;
	case Board::Direction::DOWN:
		if (cursor_pos_.y > 0)
			--cursor_pos_.y;
		break;
	case Board::Direction::LEFT:
		if (cursor_pos_.x > 0)
			--cursor_pos_.x;
		break;
	default:
		break;
	}

	cursor->setPosition({ cursor_pos_.x * block_size_ - cursor_offset_, cursor_pos_.y * block_size_ - cursor_offset_ });
}
void Board::Swap() {
	auto& block1 = squares[cursor_pos_.y][cursor_pos_.x];
	auto& block2 = squares[cursor_pos_.y][cursor_pos_.x + 1];
	if (block1->state != Square::State::IDLE || block2->state != Square::State::IDLE)
		return;

	if (!squares[cursor_pos_.y + 1][cursor_pos_.x]->IsRoof() ||
		!squares[cursor_pos_.y + 1][cursor_pos_.x + 1]->IsRoof())
		return;

	if (block1->IsBlock())
		block1->view->runAction(MoveTo::create(config.swap_time * config.time_step, { block_size_ * (cursor_pos_.x+1), block_size_ * cursor_pos_.y }));
	if (block2->IsBlock())
		block2->view->runAction(MoveTo::create(config.swap_time * config.time_step, { block_size_ * cursor_pos_.x, block_size_ * cursor_pos_.y }));

	scheduleOnce([&block1, &block2](float) {
		std::swap(block1, block2);
	}, config.swap_time * config.time_step, "swap" + std::to_string(cursor_pos_.x) + std::to_string(cursor_pos_.y));
	


}
void Board::Scroll() {
	AddLine(Fill::RANDOMLY);
}

Board::Board(Session& config) : config(config), block_size_(15.f), cursor_pos_(0, 0), time_step_(0.f) {
	squares.resize(config.real_height);
	for (auto& line : squares) {
		line.reserve(config.width);
		for (uint32_t i = 0; i < config.width; ++i)
			line.push_back(std::make_unique<Empty>());

	}
}

bool Board::init(cocos2d::Size size) {
	if (!Node::init())
		return false;

	setContentSize(size);

	auto frame = DrawNode::create();
	frame->drawRect({ 0, 0 }, { getContentSize().width, getContentSize().height }, { 1.f, 1.f, 1.f, 1.f });
	addChild(frame);

	cursor = Sprite::create("cursor.png");
	cursor->getTexture()->setAliasTexParameters();

	block_size_ = size.width / config.width;
	cursor_offset_ = block_size_ * 2 / 15.f;

	cursor->setScale(block_size_ / 15.f);
	cursor->setAnchorPoint({ 0.f, 0.f });
	cursor->setPosition({0,0});
	addChild(cursor, 100);

	fps = Label::create();
	fps->setPosition({ -100.f, 0.f });
	addChild(fps);

	scheduleUpdate();

	return true;
}


void Board::update(float delta) {
	time_step_ += delta;
	if (time_step_ >= config.time_step) {
		PhysicStep();
		time_step_ = 0;
	}
}

void Board::PhysicStep() {
	uint32_t i = 0, j = 0;
	for (auto& line : squares) {
		j = 0;
		for (auto& block : line) {
			if (!block->IsBlock()) {
				++j;
				continue;
			}

			// Should be hanging?
			if (i != 0 && block->state == Block::State::IDLE) {
				auto& block_below = squares[i - 1][j];
				if (!block_below->IsGround()) {
					block->state = Block::State::HANGING;
					block->progression = 0.f;
				}
			}
			//Hanging check
			if (block->state == Block::State::HANGING) {
				++block->progression;
				if (block->progression > config.hanging_time) {
					block->state = Block::State::WAIT;
					block->progression = 0.f;
				}
			}

			// Should be falling?
			if (block->state == Block::State::WAIT) {
				++block->progression;
				if (i == 0) {
					block->state = Block::State::IDLE;
					return;
				}
				else if (squares[i - 1][j]->IsGround()) {
					block->state = Block::State::IDLE;
				}

				// Falling check
				else if (block->progression >= config.falling_time) {
					auto& block_below = squares[i - 1][j];
					block->state = Block::State::WAIT;
					block->progression = 0.f;
					if (!block_below->IsBlock()) {
						block->view->setPositionY((i - 1) * block_size_);
						std::swap(block, block_below);
					}
				}
			}

			if (block->state == Block::State::IDLE) {
				// Should be dying ?
				int32_t left_check, right_check;
				for (left_check = j - 1; left_check >= 0; --left_check) {
					auto& b = squares[i][left_check];
					if (!b->IsBlock() || b->state != Block::State::IDLE || b->color != block->color)
						break;
				}
				for (right_check = j + 1; right_check < config.width; ++right_check) {
					auto& b = squares[i][right_check];
					if (!b->IsBlock() || b->state != Block::State::IDLE || b->color != block->color)
							break;
				}

				int32_t up_check, bottom_check;
				for (bottom_check = i - 1; bottom_check >= 0; --bottom_check) {
					auto& b = squares[bottom_check][j];
					if (!b->IsBlock() || b->color != block->color)
						break;
				}
				for (up_check = i + 1; up_check < config.width; ++up_check) {
					auto& b = squares[up_check][j];
					if (!b->IsBlock() || b->color != block->color)
						break;
				}
				// Horizontal dying blocks
				if (right_check - left_check > 3) {
					for (uint32_t a = left_check + 1; a < right_check ; ++a) {
						auto& dblock = squares[i][a];
						dblock->state = Block::State::DYING;
						dblock->view->setColor({ 50, 50, 50 });
						dblock->progression = 0.f;
					}
				}

				// Vertical dying blocks
				if (up_check - bottom_check > 3) {
					for (uint32_t a = bottom_check + 1; a < up_check; ++a) {
						auto& dblock = squares[a][j];
						dblock->state = Block::State::DYING;
						dblock->view->setColor({ 50, 50, 50 });
						dblock->progression = 0.f;
					}
				}
			}

			// Dying check
			if (block->state == Block::State::DYING) {
				++block->progression;
				if (block->progression > config.dying_time) {
					block = std::make_unique<Empty>();
				}
			}

			++j;
		}
		++i;
	}
}

Board* Board::create(Session& config, cocos2d::Size size) {
	Board* node = new Board(config);
	if (node->init(size)) {
		node->autorelease();
		return node;
	}
	CC_SAFE_DELETE(node);
	return nullptr;
}