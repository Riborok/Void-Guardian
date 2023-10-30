﻿#pragma once
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <corecrt_math_defines.h>

namespace GeomAuxiliaryFunc {
    constexpr float ANGLE_EPSILON = 0.01f;
    
    /**
     * Calculates the midpoint between two sf::Vector2f points.
     * @param point1 The first point.
     * @param point2 The second point.
     * @return The midpoint as an sf::Vector2f.
     */
    inline sf::Vector2f calcMidpoint(const sf::Vector2f &point1, const sf::Vector2f &point2) {
        return {(point1.x + point2.x) / 2, (point1.y + point2.y) / 2};
    }

    /**
     * Calculates the dot product of two sf::Vector2f vectors.
     * @param vector1 The first vector.
     * @param vector2 The second vector.
     * @return The dot product as a float.
     */
    inline float dotProduct(const sf::Vector2f &vector1, const sf::Vector2f &vector2) {
        return vector1.x * vector2.x + vector1.y * vector2.y;
    }

    /**
     * Checks if two angles are approximately orthogonal in radians.
     * @param angle1 - The first angle in radians.
     * @param angle2 - The second angle in radians.
     * @returns True if the angles are approximately orthogonal, otherwise false.
     */
    inline bool areOrthogonal(const float angle1, const float angle2) {
        return std::abs(std::abs(angle1 - angle2) - M_PI_2) < ANGLE_EPSILON;
    }

    /**
     * Normalizes the provided sf::Vector2f.
     * @param vector The vector to be normalized. This vector will be modified.
     */
    inline void normalize(sf::Vector2f &vector) {
        const float length = std::sqrt(vector.x * vector.x + vector.y * vector.y);
    
        if (length > 0) {
            vector.x /= length;
            vector.y /= length;
        }
    }

    /**
     * Calculates the Euclidean distance between two points in a 2D space.
     * @param point1 - The first point with x and y coordinates.
     * @param point2 - The second point with x and y coordinates.
     * @returns The Euclidean distance between the two points.
     */
    inline float calcDistance(const sf::Vector2f &point1, const sf::Vector2f &point2) {
        const float dx = point2.x - point1.x;
        const float dy = point2.y - point1.y;
        return std::sqrt(dx * dx + dy * dy);
    }
}