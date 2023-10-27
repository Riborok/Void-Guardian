#pragma once
#include <SFML/System/Vector2.hpp>
#include <cmath>

#define ANGLE_EPSILON 0.01

namespace GeomAuxiliaryFunc
{
    /**
     * Calculates the midpoint between two sf::Vector2f points.
     * @param point1 The first point.
     * @param point2 The second point.
     * @return The midpoint as an sf::Vector2f.
     */
    #define CALC_MIDPOINT(point1, point2) sf::Vector2f(((point1).x + (point2).x) / 2, ((point1).y + (point2).y) / 2)

    /**
     * Calculates the dot product of two sf::Vector2f vectors.
     * @param vector1 The first vector.
     * @param vector2 The second vector.
     * @return The dot product as a float.
     */
    #define DOT_PRODUCT(vector1, vector2) ((vector1).x * (vector2).x + (vector1).y * (vector2).y)

    /**
     * Normalizes the provided sf::Vector2f.
     * @param vector The vector to be normalized. This vector will be modified.
     */
    inline void normalize(sf::Vector2f& vector) {
        const float length = std::sqrt(vector.x * vector.x + vector.y * vector.y);
    
        if (length > 0) {
            vector.x /= length;
            vector.y /= length;
        }
    }

    /**
     * Checks if two angles are approximately orthogonal in radians.
     * @param angle1 - The first angle in radians.
     * @param angle2 - The second angle in radians.
     * @returns True if the angles are approximately orthogonal, otherwise false.
     */
    #define ARE_ORTHOGONAL(angle1, angle2) (std::abs(std::abs((angle1) - (angle2)) - M_PI / 2) < ANGLE_EPSILON)
}