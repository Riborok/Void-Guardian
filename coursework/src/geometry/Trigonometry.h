#pragma once

#include <corecrt_math_defines.h>
#include <cmath>

namespace Trigonometry {
    constexpr float DEGREES_TO_RADIANS = static_cast<float>(M_PI) / 180.0f;
    constexpr float M_3_MULT_PI_2 = 3.0f * static_cast<float>(M_PI_2);
    constexpr float M_2_MULT_PI = 2.0f * static_cast<float>(M_PI);

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

    /**
     * Clamps an angle to the specified range, defaulting to [0, 2π).
     * @param angle - The input angle in radians.
     * @param min_range - The minimum angle value of the range (default: 0).
     * @param max_range - The maximum angle value of the range (default: 2π).
     * @returns The angle clamped within the specified range.
     */
    inline float clampAngle(float angle, const float min_range = 0.0f, const float max_range = M_2_MULT_PI) {
        while (angle < min_range)
            angle += max_range - min_range;
        while (angle >= max_range)
            angle -= max_range - min_range;
    
        return angle;
    }

    /**
     * Checks whether an angle is in the 3rd or 4th quadrant.
     * @param angle - The input angle in radians.
     * @returns `true` if the angle is in the 3rd or 4th quadrant, `false` otherwise.
     */
    inline bool isAngleInQuadrant2Or3(float angle) {
        angle = clampAngle(angle);
        return angle > static_cast<float>(M_PI_2) && angle < M_3_MULT_PI_2;
    }

    /**
     * Checks whether the angle of the vector is in the 3rd or 4th quadrant.
     * @param vector - The input sf::Vector2f.
     * @returns `true` if the angle of the vector is in the 3rd or 4th quadrant, `false` otherwise.
     */
    inline bool isAngleInQuadrant2Or3(const sf::Vector2f &vector) {
        return isAngleInQuadrant2Or3(std::atan2(vector.y, vector.x));
    }
}