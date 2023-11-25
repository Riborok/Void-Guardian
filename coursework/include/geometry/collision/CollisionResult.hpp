#pragma once
#include <SFML/System/Vector2.hpp>

struct CollisionResult final {
    sf::Vector2f collision_point;
    float overlap;
    CollisionResult(const sf::Vector2f &collision_point, const float overlap):
        collision_point(collision_point), overlap(overlap){ }
    CollisionResult() = default;
};
