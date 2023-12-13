#pragma once
#include <random>

namespace RandomGenerator {
    int getRandom(std::uniform_int_distribution<int> &distribution);
    size_t getRandom(std::uniform_int_distribution<size_t> &distribution);
    float getRandom(std::uniform_real_distribution<float> &distribution);
}