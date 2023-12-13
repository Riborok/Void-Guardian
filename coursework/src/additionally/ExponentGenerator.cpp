#include "../../include/additionally/ExponentGenerator.hpp"

ExponentGenerator::ExponentGenerator(const int min, const int max, const float exponent):
    _min(min), _max(max), _exponent(exponent) {}

int ExponentGenerator::generate() const {
    const auto random_value = RandomGenerator::getRandom(_distribution);
    const float raised_value = std::pow(random_value, _exponent);
    const auto range = static_cast<float>(_max - _min);
    return _min + static_cast<int>(std::round(raised_value * range));
}

float getExponent(const size_t lvl) {
    if (lvl < FIRST_THRESHOLD)
        return static_cast<float>(FIRST_THRESHOLD - lvl);

    if (lvl < SECOND_THRESHOLD)
        return 1 / static_cast<float>(2 + lvl - FIRST_THRESHOLD);    

    return 1 / static_cast<float>(2 + SECOND_THRESHOLD - FIRST_THRESHOLD);
}

constexpr int START_GUN_NUM = 1;
constexpr int END_GUN_NUM = 15;
ExponentGenerator createGunNumGenerator(const size_t lvl) {
    return {START_GUN_NUM, END_GUN_NUM, getExponent(lvl)};
}