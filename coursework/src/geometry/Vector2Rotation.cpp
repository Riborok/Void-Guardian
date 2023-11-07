#include "../../include/geometry/Vector2Rotation.hpp"

namespace Vector2Rotation {
    void rotateVector2AroundTarget(sf::Vector2f &vector, const sf::Vector2f &target_point, const float sin, const float cos) {
        const float delta_x = vector.x - target_point.x;
        const float delta_y = vector.y - target_point.y;
    
        vector.x = target_point.x + delta_x * cos - delta_y * sin;
        vector.y = target_point.y + delta_x * sin + delta_y * cos;
    }

    void rotateVector2(sf::Vector2f &vector, const float sin, const float cos) {
        const float x = vector.x;
        const float y = vector.y;
    
        vector.x = x * cos - y * sin;
        vector.y = x * sin + y * cos;
    }
}
