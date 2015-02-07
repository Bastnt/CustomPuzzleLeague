#ifndef __BOARD_H__
#define __BOARD_H__

#include <vector>
#include <deque>
#include <string>
#include <array>
#include <stdint.h>
#include <memory>

#include "2d/CCDrawNode.h"
#include "2d/CCSprite.h"
#include "2d\CCLabel.h"
#include "session.h"

class Square {
public:
	enum class State : unsigned char { IDLE, HANGING, FALLING, FALLING_END, WAIT, DYING };

	cocos2d::Sprite* view;
	uint8_t color;
	State state;
	float progression;

	Square() : state(State::IDLE) {}
	virtual ~Square() {}
	Square(uint8_t color) : color(color), state(State::IDLE), progression(0.f) {}
	virtual bool IsBlock() const {
		return true;
	}

	virtual bool IsGround() const {
		return state == State::DYING || state == State::IDLE;
	}

	virtual bool IsRoof() const {
		return state == State::DYING || state == State::IDLE;
	}
};

class Block : public Square {
public:
	Block(cocos2d::Node* parent_view, float width, uint8_t color);
	~Block();
};

class Empty : public Square {
	virtual bool IsBlock() const override {
		return false;
	}

	virtual bool IsGround() const override {
		return false;
	}

	virtual bool IsRoof() const override {
		return true;
	}
};


class Board : public cocos2d::Node {
private:
	class Position {
	public:
		Position(uint32_t x, uint32_t y) : x(x), y(y) {}
		uint32_t x, y;
	};
	std::vector<std::string> block_paths_;
	float block_size_;
	Position cursor_pos_;
	float cursor_offset_;
	cocos2d::Sprite* cursor;
	float time_step_;
	Board(Session& config);

public:
	cocos2d::Label *fps;
	enum class Fill : unsigned char { EMPTY, RANDOMLY };
	std::deque<std::vector<std::unique_ptr<Square> > > squares;
	void AddLine(Fill filling = Fill::EMPTY);
	Session config;
	enum class Direction : unsigned char { UP, RIGHT, DOWN, LEFT };
	void MoveCursor(Direction d);
	void Swap();
	void Scroll();
	bool init(cocos2d::Size size);
	virtual void update(float delta) override;
	static Board* create(Session& matrix, cocos2d::Size size);
	void PositionViews();
	void PhysicStep();
};

#endif