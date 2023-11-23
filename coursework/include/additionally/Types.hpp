#pragma once

#include <utility>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>

typedef std::pair<sf::Vector2i, sf::Vector2i> MinMaxPoint;

struct Control final {
    sf::Keyboard::Key move;
    sf::Keyboard::Key shoot;
};

struct TransformParams final {
    sf::Vector2f origin;
    sf::Vector2f scale;
    TransformParams(const sf::Vector2f& origin, const sf::Vector2f& scale)
        : origin(origin), scale(scale) {}
};

struct CollisionResult final {
    sf::Vector2f collision_point;
    float overlap;
};