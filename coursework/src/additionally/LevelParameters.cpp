#include "../../include/additionally/LevelParameters.hpp"

float getExponent(const size_t lvl) {
    if (lvl < LevelParameters::FIRST_THRESHOLD)
        return static_cast<float>(LevelParameters::FIRST_THRESHOLD - lvl);

    if (lvl < LevelParameters::SECOND_THRESHOLD)
        return 1 / static_cast<float>(2 + lvl - LevelParameters::FIRST_THRESHOLD);    

    return 1 / static_cast<float>(2 + LevelParameters::SECOND_THRESHOLD - LevelParameters::FIRST_THRESHOLD);
}

constexpr int START_GUN_NUM = 1;
constexpr int END_GUN_NUM = 15;
ExponentGenerator LevelParameters::createGunNumGenerator(const size_t lvl) {
    return {START_GUN_NUM, END_GUN_NUM, getExponent(lvl)};
}

constexpr int START_BACKGROUND_NUM = 0;
int LevelParameters::getBackgroundNum(const size_t lvl) {
    if (lvl < FIRST_THRESHOLD)
        return START_BACKGROUND_NUM;

    if (lvl < SECOND_THRESHOLD)
        return START_BACKGROUND_NUM + 1;    

    return START_BACKGROUND_NUM + 2;
}

constexpr int START_BOUNDARY_NUM = 0;
int LevelParameters::getBoundaryNum(const size_t lvl) {
    if (lvl < FIRST_THRESHOLD)
        return lvl < FIRST_THRESHOLD / 2 ? START_BOUNDARY_NUM : START_BOUNDARY_NUM + 1;

    if (lvl < SECOND_THRESHOLD)
        return START_BOUNDARY_NUM + 2;    

    return START_BOUNDARY_NUM + 3;
}