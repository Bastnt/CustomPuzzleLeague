#include "random_generator.h"
#include <time.h>

RandomGenerator RandomGenerator::instance {};

RandomGenerator::RandomGenerator() : percent_(0.f, 1.f), pof_(0.5f)
{
	Init(time(NULL));
}

void RandomGenerator::Init(uint32_t seed)
{
	range.seed(seed);
}

bool RandomGenerator::PoF()
{
	return pof_(range);
}
float RandomGenerator::Percent()
{
	return percent_(range);
}

uint32_t RandomGenerator::Rand(uint32_t min, uint32_t max)
{
	std::uniform_int_distribution<uint32_t> tmp(min, max);
	return tmp(range);
}

std::mt19937& RandomGenerator::GetRange()
{
	return range;
}

float RandomGenerator::RandF(float min, float max)
{
	std::uniform_real_distribution<float> tmp(min, max);
	return tmp(range);
}