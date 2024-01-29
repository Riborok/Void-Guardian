#pragma once
#include <SFML/System/Vector2.hpp>

#include "ElementType.hpp"

struct ElementInfo final {
    sf::Vector2f point;
    float angle;
    ElementType type;
    size_t num;
    sf::Vector2f scale;
    ElementInfo(const sf::Vector2f& point, const float angle,
                const ElementType type, const size_t num, const sf::Vector2f& scale) :
        point(point), angle(angle), type(type), num(num), scale(scale) { }
};
