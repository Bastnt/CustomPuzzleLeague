#include <random>
#include "board.h"
#include "random_generator.h"
#include "2d/CCSprite.h"

USING_NS_CC;

Block::Block(uint8_t color) : color(color), progression(0.f), state(Block::State::IDLE) {}

Matrix::Matrix(Session& config) : config(config) {}

void Matrix::AddLine(Fill filling) {
	lines.push_back(std::vector<std::unique_ptr<Block> >(config.width));

	if (filling == Fill::EMPTY) {
		for (auto& b : lines.back()) {
			b = nullptr;
		}
	}

	else if (filling == Fill::RANDOMLY) {
		auto maximum = config.max_color - 1;
		for (auto& b : lines.back()) {
			b = std::make_unique<Block>(static_cast<uint8_t>(RandomGenerator::instance.Rand(0, maximum)));
		}
	}
}

void Board::MoveCursor(Board::Direction d) {
	switch (d) {
	case Board::Direction::UP:
		if (cursor_pos_.y < matrix_.config.height - 1)
			++cursor_pos_.y;
		break;
	case Board::Direction::RIGHT:
		if (cursor_pos_.x < matrix_.config.width - 2)
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

	cursor->setPosition({ cursor_pos_.x * (block_size_ + padding_size_) - cursor_offset_, cursor_pos_.y * (block_size_ + padding_size_) - cursor_offset_ });
}
void Board::Swap() {
	auto exchange = matrix_.lines[cursor_pos_.y].begin() + cursor_pos_.x;
	std::iter_swap(exchange, exchange + 1);
}
void Board::Scroll() {
	matrix_.AddLine(Matrix::Fill::RANDOMLY);
}

Board::Board(Matrix& matrix) : matrix_(matrix), block_size_(15.f), cursor_pos_(0, 0) {}

bool Board::init(cocos2d::Size size) {
	if (!Node::init())
		return false;

	setContentSize(size);

	auto frame = DrawNode::create();
	frame->drawRect({ 0, 0 }, { getContentSize().width, getContentSize().height }, { 1.f, 1.f, 1.f, 1.f });
	addChild(frame);

	cursor = Sprite::create("cursor.png");
	cursor->getTexture()->setAliasTexParameters();
	for (uint32_t i = 0; i < matrix_.config.max_color; ++i) {
		block_paths_.push_back(std::to_string(i) + ".png");
	}

	block_size_ = size.width / (matrix_.config.width + (1 / 15.f)*(matrix_.config.width - 1));
	padding_size_ = block_size_ * 1 / 15.f;
	cursor_offset_ = block_size_ * 2 / 15.f;

	cursor->setScale(block_size_ / 15.f);
	cursor->setAnchorPoint({ 0.f, 0.f });
	cursor->setPosition({0,0});
	addChild(cursor, 100);

	return true;
}


void Board::draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t flags) {
	float i=0, j=0;
	for (auto& line : matrix_.lines) {
		i = 0;
		for (auto& block : line) {
			if (!block)
				continue;
			cocos2d::Mat4 result = transform;
			result.translate({ i, j, 0.f });
			result.scale({ block_size_ / 15.f, block_size_/15.f, 1.f });
			auto s = Sprite::create(block_paths_[block->color]);
			s->getTexture()->setAliasTexParameters();
			s->draw(renderer, result, flags);
			i += block_size_ + padding_size_;
		}
		j += block_size_ + padding_size_;
	}
}

void Board::update(float delta) {

}

Board* Board::create(Matrix& matrix, cocos2d::Size size) {
	Board* node = new Board(matrix);
	if (node->init(size)) {
		node->autorelease();
		return node;
	}
	CC_SAFE_DELETE(node);
	return nullptr;
}