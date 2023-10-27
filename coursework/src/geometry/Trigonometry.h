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
    #define SIN_DEGREES(degrees) (std::sin((degrees) * Trigonometry::DEGREES_TO_RADIANS))

    /**
    * Calculates the cosine of an angle in degrees.
    * @param degrees The angle in degrees.
    * @return The cosine of the given angle in radians.
    */
    #define COS_DEGREES(degrees) (std::cos((degrees) * Trigonometry::DEGREES_TO_RADIANS))
}