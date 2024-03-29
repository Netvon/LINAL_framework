#pragma once
#include <random>

class RandomGenerator
{
private:

	RandomGenerator() {};
	std::random_device rd;
	std::mt19937 generator{ rd() };
public:
	static RandomGenerator& instance();

	RandomGenerator(RandomGenerator const&) = delete;
	void operator=(RandomGenerator const&) = delete;

	int operator()(int min, int max);
	size_t operator()(size_t min, size_t max);
	float operator()(float min, float max);
};

#define random RandomGenerator::instance()