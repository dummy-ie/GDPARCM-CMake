#include "RandomUtils.h"

using namespace gd;

// Define static members
std::random_device RandomUtils::rd;
std::mt19937 RandomUtils::gen(rd());  // Seeded once