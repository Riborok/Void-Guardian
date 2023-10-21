#pragma once
#include <SFML/System/Vector2.hpp>

namespace Vector2Rotation {
    /**
     * Rotates a vector (sf::Vector2f) around a target point by a given sine and cosine.
     * @param vector The vector to rotate.
     * @param target_point The target point to rotate around.
     * @param sin The sine of the rotation angle.
     * @param cos The cosine of the rotation angle.
     */
    inline void RotateVector2AroundTarget(sf::Vector2f &vector, const sf::Vector2f &target_point, const float sin, const float cos) {
        const float delta_x = vector.x - target_point.x;
        const float delta_y = vector.y - target_point.y;
    
        vector.x = target_point.x + delta_x * cos - delta_y * sin;
        vector.y = target_point.y + delta_x * sin + delta_y * cos;
    }

    /**
     * Rotates a vector (sf::Vector2f) by a given sine and cosine.
     * @param vector The vector to rotate.
     * @param sin The sine of the rotation angle.
     * @param cos The cosine of the rotation angle.
     */
    inline void RotateVector2(sf::Vector2f &vector, const float sin, const float cos) {
        const float x = vector.x;
        const float y = vector.y;
    
        vector.x = x * cos - y * sin;
        vector.y = x * sin + y * cos;
    }
}
