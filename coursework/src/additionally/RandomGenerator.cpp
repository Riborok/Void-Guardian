#include "../../include/additionally/RandomGenerator.hpp"

std::mt19937 gen(std::random_device{}());

int RandomGenerator::getRandom(std::uniform_int_distribution<int> &distribution) { return distribution(gen); }
size_t RandomGenerator::getRandom(std::uniform_int_distribution<size_t> &distribution) { return distribution(gen); }
float RandomGenerator::getRandom(std::uniform_real_distribution<float> &distribution) { return distribution(gen); }