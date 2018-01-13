#include "RandomGenerator.h"

RandomGenerator & RandomGenerator::instance()
{
	static RandomGenerator rg;
	return rg;
}

int RandomGenerator::operator()(int min, int max)
{
	std::uniform_int_distribution<> dis(min, max);
	return dis(generator);
}

size_t RandomGenerator::operator()(size_t min, size_t max)
{
	std::uniform_int_distribution<size_t> dis(min, max);
	return dis(generator);
}

float RandomGenerator::operator()(float min, float max)
{
	std::uniform_real_distribution<float> dis(min, max);
	return dis(generator);
}
