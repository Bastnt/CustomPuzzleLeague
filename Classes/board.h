#ifndef __BOARD_H__
#define __BOARD_H__

#include <vector>
#include <string>
#include <array>
#include <stdint.h>
#include <memory>
#include "2d/CCDrawNode.h"
#include "2d/CCSprite.h"
#include "session.h"

class Block {
public:
	enum class State : unsigned char { IDLE, FALLING, DYING };
	float progression;
	State state;
	uint8_t color;
	cocos2d::Sprite* block_view_;

	Block(uint8_t color);
};

class Matrix {
public:

	enum class Fill : unsigned char {EMPTY, RANDOMLY};
	std::vector<std::vector<std::unique_ptr<Block> > > lines;
	void AddLine(Fill filling = Fill::EMPTY);
	Session config;
	Matrix(Session& config);
};

class Board : public cocos2d::DrawNode {
private:
	class Position {
	public:
		Position(uint32_t x, uint32_t y) : x(x), y(y) {}
		uint32_t x, y;
	};
	std::vector<std::string> block_paths_;
	Matrix& matrix_;
	float block_size_;
	float padding_size_;
	Position cursor_pos_;
	float cursor_offset_;
	cocos2d::Sprite* cursor;

	Board(Matrix& matrix);
public:
	enum class Direction : unsigned char { UP, RIGHT, DOWN, LEFT };
	void MoveCursor(Direction d);
	void Swap();
	void Scroll();
	bool init(cocos2d::Size size);
	virtual void update(float delta) override;
	static Board* create(Matrix& matrix, cocos2d::Size size);
	virtual void Board::draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t flags) override;
};

#endif