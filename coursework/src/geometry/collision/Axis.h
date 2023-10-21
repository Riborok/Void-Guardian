#pragma once
#include <SFML/System/Vector2.hpp>

#include "../GeomAuxiliaryFunc.h"

class Axis final : public sf::Vector2f {
public:
    Axis(const sf::Vector2f v1, const sf::Vector2f v2) : sf::Vector2f(v1.y - v2.y, v2.x - v1.x) {
        GeomAuxiliaryFunc::Normalize(*this);
    }

    ~Axis() noexcept = default;
    Axis(const Axis&) noexcept = default;
    Axis& operator=(const Axis&) noexcept = default;
    Axis(Axis&&) noexcept = default;
    Axis& operator=(Axis&&) noexcept = default;
};
