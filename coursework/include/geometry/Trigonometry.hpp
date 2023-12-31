﻿#pragma once

#include <corecrt_math_defines.h>
#include <SFML/System/Vector2.hpp>

namespace Trigonometry {
    constexpr float M_PI_ = M_PI;
    constexpr float M_PI_2_ = M_PI_2;
    constexpr float M_3_MULT_PI_2_ = 3.0f * M_PI_2_;
    constexpr float M_2_MULT_PI_ = 2.0f * M_PI_;
 
    constexpr float EPSILON_RADIANS = 0.0175f;
    constexpr float EPSILON_DEGREES  = 1.0f;

    /**
     * Converts degrees to radians.
     * @param degrees The angle in degrees.
     * @return The equivalent angle in radians.
     */
    float degreesToRadians(const float degrees);

    /**
     * Converts radians to degrees.
     * @param radians The angle in radians.
     * @return The equivalent angle in degrees.
     */
    float radiansToDegrees(const float radians);
 
    /**
     * Calculates the sine of an angle in degrees.
     * @param degrees The angle in degrees.
     * @return The sine of the given angle in radians.
     */
    float sinDegrees(const float degrees);

    /**
     * Calculates the cosine of an angle in degrees.
     * @param degrees The angle in degrees.
     * @return The cosine of the given angle in radians.
     */
    float cosDegrees(const float degrees);

    /**
    * Calculates the sine of an angle in radians.
    * @param radians The angle in radians.
    * @return The sine of the given angle.
    */
    float sinRadians(const float radians);

    /**
     * Calculates the cosine of an angle in radians.
     * @param radians The angle in radians.
     * @return The cosine of the given angle.
     */
    float cosRadians(const float radians);

    /**
     * Clamps an angle to the specified range, defaulting to [0, 2π).
     * @param angle - The input angle in radians.
     * @param min_range - The minimum angle value of the range (default: 0).
     * @param max_range - The maximum angle value of the range (default: 2π).
     * @returns The angle clamped within the specified range.
     */
    float clampAngle(float angle, const float min_range = 0.0f, const float max_range = M_2_MULT_PI_);

    /**
     * Checks whether an angle is in the 3rd or 4th quadrant.
     * @param angle - The input angle in radians.
     * @returns `true` if the angle is in the 3rd or 4th quadrant, `false` otherwise.
     */
    bool isAngleInQuadrant2Or3(float angle);

    /**
     * Checks whether the angle of the vector is in the 3rd or 4th quadrant.
     * @param vector - The input vector.
     * @returns `true` if the angle of the vector is in the 3rd or 4th quadrant, `false` otherwise.
     */
    bool isAngleInQuadrant2Or3(const sf::Vector2f &vector);
}