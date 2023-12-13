#pragma once
#include "RandomGenerator.hpp"

class ExponentGenerator final {
    mutable std::uniform_real_distribution<float> _distribution{0.0, 1.0};
    int _min;
    int _max;
    float _exponent;
public:
    ExponentGenerator(const int min, const int max, const float exponent);
    int generate() const;
    
    ~ExponentGenerator() noexcept = default;
    ExponentGenerator(ExponentGenerator&&) noexcept = delete;
    ExponentGenerator& operator=(ExponentGenerator&&) noexcept = delete;
    ExponentGenerator(const ExponentGenerator&) noexcept = delete;
    ExponentGenerator& operator=(const ExponentGenerator&) noexcept = delete;
};

constexpr size_t FIRST_THRESHOLD = 6;
constexpr size_t SECOND_THRESHOLD = 9;
/**
 * A function that creates an ExponentGenerator based on the input level (FIRST_THRESHOLD is 6 and SECOND_THRESHOLD is 9).
 * 
 * - For levels below FIRST_THRESHOLD, the generator produces larger exponents with lower probability, as
 *   the result is the difference between FIRST_THRESHOLD and the input level.
 * 
 * - For levels between FIRST_THRESHOLD and (SECOND_THRESHOLD - 1), the generator produces larger exponents
 *   with higher probability, as the result is based on the formula 1 / (2 + level - FIRST_THRESHOLD).
 * 
 * - For levels equal to or above SECOND_THRESHOLD, the generator consistently produces a constant exponent
 *   of 1 / (2 + SECOND_THRESHOLD - FIRST_THRESHOLD).
 * 
 * @param lvl The input level for which to create the ExponentGenerator.
 * @return An ExponentGenerator that follows the described behavior.
 */
ExponentGenerator createGunNumGenerator(const size_t lvl);