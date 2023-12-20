#include "../../include/additionally/ExponentGenerator.hpp"

ExponentGenerator::ExponentGenerator(const int min, const int max, const float exponent):
    _min(min), _max(max), _exponent(exponent) {}

int ExponentGenerator::generate() const {
    const auto random_value = RandomGenerator::getRandom(_distribution);
    const float raised_value = std::pow(random_value, _exponent);
    const auto range = static_cast<float>(_max - _min);
    return _min + static_cast<int>(std::round(raised_value * range));
}