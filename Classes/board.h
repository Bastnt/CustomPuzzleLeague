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
#include "block_generator.h"
#include "physic_engine.h"

class Square {
public:
	enum class State : unsigned char { IDLE, HANGING, FALLING, DYING };

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
	Block(uint8_t color);
	void Init(cocos2d::Node* parent_view, float width);
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
	struct Position {
		Position(uint32_t x, uint32_t y) : x(x), y(y) {}
		uint32_t x, y;
	};

	// The matrix containing all the blocks
	std::deque<std::vector<std::unique_ptr<Square> > > squares;
	// The current position of the cursor
	Position cursor_pos_;
	// The offset size of the cursor (so that it is correctly aligned with the blocks)
	float cursor_offset_;
	// Sprite of the cursor
	cocos2d::Sprite* cursor_;
	// Cumulated delta time, to know when to tick a Physic Step
	float time_step_;
	// Configuration of the session
	Session config_;
	PhysicEngine engine_;
	// Bottom block generator
	BlockGenerator block_generator_;

	// Private ctor for cocos2d-x
	Board(Session& config);

public:
	// cocos2d-x Node's functions
	bool init(cocos2d::Size size);
	virtual void update(float delta) override;
	static Board* create(Session& matrix, cocos2d::Size size);

	// Direction of cursor movements
	enum class Direction : unsigned char { UP, RIGHT, DOWN, LEFT };

	// Add a anew line of blocks using the creep
	void AddLine();
	// Change the cursor position
	void MoveCursor(Direction d);
	// Swap two blocks at cursor position
	void Swap();
	void Scroll();
	void MoveUp();
	void ResetPosition();
	// Reset position of all block views in squares_
	void PositionViews();
};

#endif