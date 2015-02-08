#include <algorithm>

#include "2d/CCSprite.h"
#include "2d\CCActionInterval.h"
#include "2d\CCActionInstant.h"

#include "board.h"
#include "random_generator.h"

USING_NS_CC;

void Block::Init(Node* parent_view, float width) {
	state = Block::State::IDLE;
	view = Sprite::create(std::to_string(color) + ".png");
	auto size = view->getContentSize();
	view->setScale(width / size.width, width / size.height);
	view->getTexture()->setAliasTexParameters();
	view->setAnchorPoint({ 0.f, 0.f });
	parent_view->addChild(view);
}

Block::Block(uint8_t color) : Square(color) {}

Block::~Block() {
	view->removeFromParentAndCleanup(true);
}

void Board::PositionViews() {
	float x_pos = 0.f, y_pos = 0.f;
	uint32_t height = 0;
	for (auto& line : squares) {
		x_pos = 0;
		for (auto& square : line) {
			if (square->IsBlock()) {
				square->view->setPosition({ x_pos, y_pos });
				if (height < config_.ground_height)
					square->view->setColor({ 40, 40, 40 });
				else if (height == config_.ground_height)
					square->view->setColor(Color3B::WHITE);

			}
			x_pos += config_.block_size;
		}
		y_pos += config_.block_size;
		++height;
	}
}

void Board::AddLine() {
	auto newline = block_generator_.PopLine();
	squares.pop_back();
	for (auto& block : newline)
		dynamic_cast<Block*>(block.get())->Init(this, config_.block_size);
	squares.push_front(std::move(newline));
	PositionViews();
}

void Board::MoveUp() {
	setPositionY(getPositionY() + config_.block_size / config_.block_division);
}

void Board::ResetPosition() {
	setPositionY(0.f);
}

void Board::MoveCursor(Board::Direction d) {
	switch (d) {
	case Board::Direction::UP:
		if (cursor_pos_.y < config_.height - 1)
			++cursor_pos_.y;
		break;
	case Board::Direction::RIGHT:
		if (cursor_pos_.x < config_.width - 2)
			++cursor_pos_.x;
		break;
	case Board::Direction::DOWN:
		if (cursor_pos_.y > config_.ground_height)
			--cursor_pos_.y;
		break;
	case Board::Direction::LEFT:
		if (cursor_pos_.x > 0)
			--cursor_pos_.x;
		break;
	default:
		break;
	}

	cursor_->setPosition({ cursor_pos_.x * config_.block_size - cursor_offset_, cursor_pos_.y * config_.block_size - cursor_offset_ });
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
		block1->view->runAction(MoveTo::create(config_.swap_time * config_.time_step, { config_.block_size * (cursor_pos_.x + 1), config_.block_size * cursor_pos_.y }));
	if (block2->IsBlock())
		block2->view->runAction(MoveTo::create(config_.swap_time * config_.time_step, { config_.block_size * cursor_pos_.x, config_.block_size * cursor_pos_.y }));

	scheduleOnce([&block1, &block2](float) {
		std::swap(block1, block2);
	}, config_.swap_time * config_.time_step, "swap" + std::to_string(cursor_pos_.x) + std::to_string(cursor_pos_.y));
}

void Board::Scroll() {
	AddLine();
}

Board::Board(Session& config) : config_(config), cursor_pos_(0, 0), time_step_(0.f), engine_(squares, *this, config_), block_generator_(config_) {
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

	cursor_ = Sprite::create("cursor.png");
	cursor_->getTexture()->setAliasTexParameters();

	config_.block_size = size.width / config_.width;
	cursor_offset_ = config_.block_size * 2 / 15.f;

	cursor_->setScale(config_.block_size / 15.f);
	cursor_->setAnchorPoint({ 0.f, 0.f });
	cursor_->setPosition({0,0});
	addChild(cursor_, 100);

	scheduleUpdate();

	return true;
}


void Board::update(float delta) {
	time_step_ += delta;
	if (time_step_ >= config_.time_step) {
		engine_.Step();
		time_step_ -= config_.time_step;
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