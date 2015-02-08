#ifndef __PHYSIC_ENGINE_H__
#define __PHYSIC_ENGINE_H__

#include <deque>
#include <vector>
#include <memory>

#include "session.h"
#include "block_generator.h"

class Square;
class Board;

class PhysicEngine {
private:
	std::deque<std::vector<std::unique_ptr<Square> > >& squares_;
	Board& parent_board_;
	Session& config_;
	// Cumulated delta time, to know when to tick a Physic Step
	float time_step_;
	
	// Steps between creep moves
	uint32_t creep_step_;
	// Steps bewteen newline generation
	uint32_t generate_newline_move_;

public:
	PhysicEngine(std::deque<std::vector<std::unique_ptr<Square> > >& squares, Board& parent_board, Session& config) :
		squares_(squares), parent_board_(parent_board), config_(config)
	{}
	void Step();
};

#endif