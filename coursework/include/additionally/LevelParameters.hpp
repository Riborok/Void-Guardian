#pragma once
#include "ExponentGenerator.hpp"
#include "../game/construction/game field creation/RandomSize.hpp"
#include "../game/construction/game field creation/arena/enemy spawn/EnemySpawnConfiguration.hpp"

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
     * A function that creates an ExponentGenerator for determining the number of enemies based on the input level.
     * 
     * - For levels below the FIRST_THRESHOLD, the generator produces larger exponents with lower probability,
     *   as the result is the difference between FIRST_THRESHOLD and the input level.
     * 
     * - For levels between the FIRST_THRESHOLD and (SECOND_THRESHOLD - 1), the generator produces larger exponents
     *   with higher probability, as the result is based on the formula 1 / (2 + level - FIRST_THRESHOLD).
     * 
     * - For levels equal to or above the SECOND_THRESHOLD, the generator consistently produces a constant exponent
     *   of 1 / (2 + SECOND_THRESHOLD - FIRST_THRESHOLD).
     * 
     * @param lvl The input level for which to create the ExponentGenerator.
     * @return An ExponentGenerator that follows the described behavior for determining the number of enemies.
     */
    ExponentGenerator createEnemyCharacterNumGenerator(const size_t lvl);

    /**
     * Retrieves the background number based on the input level.
     * 
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

    /**
     * Generates an EnemySpawnConfiguration based on the input level.
     * The configuration includes the number of enemies and the spawn interval.
     * 
     * @param lvl The input level for which to generate the enemy spawn configuration.
     * @return An EnemySpawnConfiguration corresponding to the input level.
     */
    EnemySpawnConfiguration getEnemySpawnConfiguration(const size_t lvl);

    /**
     * Generates and returns a RandomSize object based on the input level.
     * The RandomSize object encapsulates random size distributions for the arena.
     * 
     * @param lvl The input level for which to generate the random size configuration.
     * @return A RandomSize object corresponding to the input level.
     */
    RandomSize getArenaRandomSize(const size_t lvl);
}