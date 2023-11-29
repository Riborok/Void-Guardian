#pragma once
#include <SFML/System/Vector2.hpp>

namespace Vector2Rotation {
    /**
     * Rotates a vector around a target point by a given sine and cosine.
     * @param vector The vector to rotate.
     * @param target_point The target point to rotate around.
     * @param sin The sine of the rotation angle.
     * @param cos The cosine of the rotation angle.
     */
    void rotateVector2AroundTarget(sf::Vector2f &vector, const sf::Vector2f &target_point, const float sin, const float cos);

    /**
     * Rotates a vector by a given sine and cosine.
     * @param vector The vector to rotate.
     * @param sin The sine of the rotation angle.
     * @param cos The cosine of the rotation angle.
     */
    void rotateVector2(sf::Vector2f &vector, const float sin, const float cos);

    /**
     * Rotates a vector by 90 degrees counterclockwise.
     * @param vector The vector to rotate.
     */
    void rotate90Degrees(sf::Vector2f &vector);

    /**
     * Rotates a vector by 180 degrees counterclockwise.
     * @param vector The vector to rotate.
     */
    void rotate180Degrees(sf::Vector2f &vector);

    /**
     * Rotates a vector by 270 degrees counterclockwise.
     * @param vector The vector to rotate.
     */
    void rotate270Degrees(sf::Vector2f &vector);

    /**
     * Rotates a vector by 45 degrees counterclockwise.
     * @param vector The vector to rotate.
     */
    void rotate45Degrees(sf::Vector2f &vector);

    /**
     * Rotates a vector by 135 degrees counterclockwise.
     * @param vector The vector to rotate.
     */
    void rotate135Degrees(sf::Vector2f &vector);

    /**
     * Rotates a vector by 225 degrees counterclockwise.
     * @param vector The vector to rotate.
     */
    void rotate225Degrees(sf::Vector2f &vector);

    /**
     * Rotates a vector by 315 degrees counterclockwise.
     * @param vector The vector to rotate.
     */
    void rotate315Degrees(sf::Vector2f &vector);
}