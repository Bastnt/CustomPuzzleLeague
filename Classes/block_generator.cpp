#include "block_generator.h"
#include "board.h"
#include "random_generator.h"

BlockGenerator::BlockGenerator(Session& config) : config_(config) {
	buffer_.push(GenerateLine());
	buffer_.push(GenerateLine());
}

std::vector<std::unique_ptr<Square> > BlockGenerator::PopLine() {
	auto newline = std::vector<std::unique_ptr<Square> >();
	uint32_t color;
	auto maximum = config_.max_color - 1;

	for (uint32_t i = 0; i < config_.width; ++i) {
		color = RandomGenerator::instance.Rand(0, maximum);
		if (i > 1 && color == newline[i - 1]->color && color == newline[i - 2]->color)
			color = (color + 1) % config_.max_color;
		if (color == buffer_.front()[i]->color && color == buffer_.back()[i]->color)
			color = (color + 1) % config_.max_color;
		newline.push_back(std::make_unique<Block>(color));
	}

	auto ret = std::move(buffer_.front());
	buffer_.pop();
	buffer_.push(std::move(newline));
	return ret;
}

std::vector<std::unique_ptr<Square> > BlockGenerator::GenerateLine() {
	std::vector<std::unique_ptr<Square> > ret;
	ret.reserve(config_.width);
	uint32_t color;
	auto maximum = config_.max_color - 1;
	for (uint32_t i = 0; i < config_.width; ++i) {
		color = RandomGenerator::instance.Rand(0, maximum);
		if (i > 1 && color == ret[i - 1]->color && color == ret[i - 2]->color)
			color = color + 1 % config_.max_color;
		ret.push_back(std::make_unique<Block>(color));
	}
	return ret;
}