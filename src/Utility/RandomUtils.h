#pragma once
#include <random>

namespace gd
{
	class RandomUtils
	{
	public:
		static int getRandomInt(int min, int max) {
			static std::random_device rd;  // Random device to seed the generator
			static std::mt19937 gen(rd()); // Mersenne Twister engine
			std::uniform_int_distribution<> dist(min, max); // Uniform distribution between min and max

			return dist(gen); // Return a random number in the specified range
		}
	};
}