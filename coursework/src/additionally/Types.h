#pragma once
#include <SFML/System/Vector2.hpp>

namespace Types {
    struct CollisionResult {
         sf::Vector2f collision_point;
        float overlap;
    };
    enum ElementType : unsigned int {
        // Simple
        BACKGROUND = 0,
        BLOCK,
        GUN,

        // Animated
        WRAITH,
    };
}
