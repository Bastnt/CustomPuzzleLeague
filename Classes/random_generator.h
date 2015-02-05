#ifndef _COMPENDIUM_RANDOM_GENERATOR_H_
#define _COMPENDIUM_RANDOM_GENERATOR_H_

#include <random>
#include <memory>

class RandomGenerator
{
public:
	static RandomGenerator instance;
	void Init(uint32_t seed);

	//Launches a coin a get a result
	bool PoF();
	//Gets a random percent between 0.f included and 1.f included
	float Percent();
	//Picks a random element from the vector
	template <class T>
	T PickElement(const std::vector<T>& elements);

	uint32_t Rand(uint32_t min, uint32_t max);
	float RandF(float min, float max);

	std::mt19937&  GetRange();
private:
	RandomGenerator();
	std::mt19937 range;

	std::uniform_real_distribution<float> percent_;
	std::bernoulli_distribution pof_;

};


template <class T>
T RandomGenerator::PickElement(const std::vector<T>& elements)
{
	uint32_t pos = Rand(0, elements.size()-1);
	return elements[pos];
}

#endif