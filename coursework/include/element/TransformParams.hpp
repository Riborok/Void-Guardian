#pragma once
#include <SFML/System/Vector2.hpp>

struct TransformParams final {
    sf::Vector2f origin;
    sf::Vector2f scale;
    TransformParams(const sf::Vector2f& origin, const sf::Vector2f& scale)
        : origin(origin), scale(scale) {}
};
