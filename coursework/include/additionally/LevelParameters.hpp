#pragma once
#include "ExponentGenerator.hpp"

namespace LevelParameters {
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

    /**
     * Retrieves the background number based on the input level.
     * @param lvl The input level for which to determine the background number.
     * @return The background number corresponding to the input level.
     */
    size_t getBackgroundNum(const size_t lvl);

    /**
     * Retrieves the boundary number based on the input level.
     * 
     * @param lvl The input level for which to determine the boundary number.
     * @return The boundary number corresponding to the input level.
     */
    size_t getBoundaryNum(const size_t lvl);
}