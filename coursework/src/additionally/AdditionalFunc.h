#pragma once

#include <random>

namespace AdditionalFunc {
    namespace InnerLogic {
        std::mt19937 gen(std::random_device{}());
    }
    
    /**
     * Generates a random value using the provided distribution.
     * @param distribution The distribution to use for generating random numbers.
     * @returns A random integer based on the provided distribution.
     */
    template <typename T>
    T getRandom(std::uniform_int_distribution<T> &distribution) {
        return distribution(InnerLogic::gen);
    }
}