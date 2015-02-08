#ifndef __BLOCK_GENERATOR_H__
#define __BLOCK_GENERATOR_H__

#include <queue>
#include <vector>
#include <memory>
#include <session.h>

class Square;

class BlockGenerator {
public:
	BlockGenerator(Session& config);
	std::vector<std::unique_ptr<Square> > GenerateLine();
	std::vector<std::unique_ptr<Square> > PopLine();
private:
	std::queue<std::vector<std::unique_ptr<Square> > > buffer_;
	Session& config_;
};

#endif