#pragma once

#include <random>

namespace AdditionalFunc {
    
    /**
     * Generates a random value using the provided distribution.
     * @param distribution The distribution to use for generating random numbers.
     * @returns A random integer based on the provided distribution.
     */
    int getRandom(std::uniform_int_distribution<> &distribution);
}