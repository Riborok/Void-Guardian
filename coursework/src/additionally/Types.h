#pragma once
#include <SFML/System/Vector2.hpp>

namespace Types {
    struct CollisionResult {
         sf::Vector2f collision_point;
        float overlap;
    };

    #define AMOUNT_OF_ELEMENT_TYPE 4
    enum ElementType : unsigned int {
        // Simple
        BACKGROUND = 0u,
        BLOCK,
        GUN,

        // Animated
        WRAITH,
    };
}
