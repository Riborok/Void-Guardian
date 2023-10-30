#pragma once

#include <corecrt_math_defines.h>
#include <cmath>

namespace Trigonometry {
    constexpr float DEGREES_TO_RADIANS = static_cast<float>(M_PI) / 180.0f;

    /**
     * Calculates the sine of an angle in degrees.
     * @param degrees The angle in degrees.
     * @return The sine of the given angle in radians.
     */
    inline float sinDegrees(const float degrees) {
        return std::sin(degrees * DEGREES_TO_RADIANS);
    }

    /**
     * Calculates the cosine of an angle in degrees.
     * @param degrees The angle in degrees.
     * @return The cosine of the given angle in radians.
     */
    inline float cosDegrees(const float degrees) {
        return std::cos(degrees * DEGREES_TO_RADIANS);
    }
}