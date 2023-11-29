#pragma once
#include <SFML/System/Vector2.hpp>

struct CollisionResult final {
    sf::Vector2f collision_point;
    float overlap;
    CollisionResult() = default;
};
