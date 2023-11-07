#pragma once
#include <SFML/System/Vector2.hpp>

class Axis final : public sf::Vector2f {
public:
    Axis(const sf::Vector2f v1, const sf::Vector2f v2);

    ~Axis() noexcept = default;
    Axis(const Axis&) noexcept = default;
    Axis& operator=(const Axis&) noexcept = default;
    Axis(Axis&&) noexcept = default;
    Axis& operator=(Axis&&) noexcept = default;
};