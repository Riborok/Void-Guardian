#pragma once
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <corecrt_math_defines.h>

#include "../additionally/Constants.h"

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
     * Computes the cross product of two vectors and returns the result.
     * @param vector1 The first vector.
     * @param vector2 The second vector.
     * @returns The cross product of the input vectors.
     */
    inline float crossProduct(const sf::Vector2f &vector1, const sf::Vector2f &vector2) {
        return vector1.x * vector2.y - vector1.y * vector2.x;
    }

    /**
     * Adds two vectors together and returns the result as a new vector.
     * @param vector1 The first vector.
     * @param vector2 The second vector.
     * @returns A new vector representing the sum of the input vectors.
     */
    inline sf::Vector2f add(const sf::Vector2f &vector1, const sf::Vector2f &vector2) {
        return {vector1.x + vector2.x, vector1.y + vector2.y};
    }

    /**
     * Subtracts one vector from another and returns the result as a new vector.
     * @param minuend_vector The vector from which to subtract.
     * @param subtrahend_vector The vector to subtract.
     * @returns A new vector representing the result of the subtraction.
     */
    inline sf::Vector2f subtract(const sf::Vector2f &minuend_vector, const sf::Vector2f &subtrahend_vector) {
        return {minuend_vector.x - subtrahend_vector.x, minuend_vector.y - subtrahend_vector.y};
    }

    /**
     * Checks if two angles are approximately orthogonal in radians.
     * @param angle1 - The first angle in radians.
     * @param angle2 - The second angle in radians.
     * @returns True if the angles are approximately orthogonal, otherwise false.
     */
    inline bool areOrthogonal(const float angle1, const float angle2) {
        return std::abs(std::abs(angle1 - angle2) - static_cast<float>(M_PI_2)) < ANGLE_EPSILON;
    }

    /**
     * Calculates the length of a 2D vector.
     * @param vector The vector for which to compute the length.
     * @return The length of the input vector.
     */
    inline float calcLength(const sf::Vector2f &vector) {
        return std::sqrt(vector.x * vector.x + vector.y * vector.y);
    }

    /**
     * Normalizes the provided sf::Vector2f.
     * @param vector The vector to be normalized. This vector will be modified.
     */
    inline void normalize(sf::Vector2f &vector) {
        const float length = calcLength(vector);
    
        if (length > 0) {
            vector.x /= length;
            vector.y /= length;
        }
    }

    /**
     * Sets the length of the provided sf::Vector2f.
     * @param vector The vector whose length needs to be set.
     * @param new_length The new length for the vector.
     */
    inline void setLength(sf::Vector2f &vector, const float new_length) {
        const float length = calcLength(vector);

        if (length > 0) {
            vector.x *= new_length / length;
            vector.y *= new_length / length;
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

    /**
     * Clamps a 2D vector to the dimensions of a specified window size.
     * @param vector - The vector to be clamped.
     * @param window_size - The size of the window in which the vector is clamped.
     * @note The function wraps the vector's coordinates around the window if they go beyond its boundaries.
     */
    inline void clampVector(sf::Vector2f &vector, const sf::Vector2u &window_size) {
        const auto width = static_cast<float>(window_size.x), height = static_cast<float>(window_size.y);
        
        while (vector.x < width)
            vector.x += width;
        while (vector.x >= width)
            vector.x -= width;

        while (vector.y < height)
            vector.y +=  height;
        while (vector.y >=  height)
            vector.y -=  height;
    }
}