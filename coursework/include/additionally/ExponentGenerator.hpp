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