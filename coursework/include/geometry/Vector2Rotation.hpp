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
}