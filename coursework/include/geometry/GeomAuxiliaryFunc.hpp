#pragma once

#include <SFML/System/Vector2.hpp>

namespace GeomAuxiliaryFunc {
    /**
     * Calculates the midpoint between two points.
     * @param point1 The first point.
     * @param point2 The second point.
     * @return The midpoint as an sf::Vector2f.
     */
    sf::Vector2f calcMidpoint(const sf::Vector2f &point1, const sf::Vector2f &point2);

    /**
     * Calculates the dot product of two sf::Vector2f vectors.
     * @param vector1 The first vector.
     * @param vector2 The second vector.
     * @return The dot product as a float.
     */
    float dotProduct(const sf::Vector2f &vector1, const sf::Vector2f &vector2);

    /**
     * Computes the cross product of two vectors and returns the result.
     * @param vector1 The first vector.
     * @param vector2 The second vector.
     * @returns The cross product of the input vectors.
     */
    float crossProduct(const sf::Vector2f &vector1, const sf::Vector2f &vector2);

    /**
     * Checks if two angles are approximately orthogonal in radians.
     * @param angle1 - The first angle in radians.
     * @param angle2 - The second angle in radians.
     * @returns True if the angles are approximately orthogonal, otherwise false.
     */
    bool areOrthogonal(const float angle1, const float angle2);

    /**
     * Calculates the length of a 2D vector.
     * @param vector The vector for which to compute the length.
     * @return The length of the input vector.
     */
    float calcLength(const sf::Vector2f &vector);

    /**
     * Normalizes the provided sf::Vector2f.
     * @param vector The vector to be normalized. This vector will be modified.
     */
    void normalize(sf::Vector2f &vector);

    /**
     * Sets the length of the provided sf::Vector2f.
     * @param vector The vector whose length needs to be set.
     * @param new_length The new length for the vector.
     */
    void setLength(sf::Vector2f &vector, const float new_length);

    /**
     * Calculates the Euclidean distance between two points in a 2D space.
     * @param point1 - The first point with x and y coordinates.
     * @param point2 - The second point with x and y coordinates.
     * @returns Distance between the two points.
     */
    float calcDistance(const sf::Vector2f &point1, const sf::Vector2f &point2);

    /**
    * Multiplies two integer vectors element-wise.
    * @param vector1 - The first point with x and y coordinates.
    * @param vector2 - The second point with x and y coordinates.
    * @returns New vector resulting from the element-wise multiplication.
    */
    sf::Vector2i multiplyVectors(const sf::Vector2i& vector1, const sf::Vector2i& vector2);
}