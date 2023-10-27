#pragma once

#include <SFML/System/Vector2.hpp>

class Polygon {
public:
    virtual const size_t &pointsAmount() const = 0;
    virtual sf::Vector2f *points() = 0;
    virtual const sf::Vector2f calcCenter() const = 0;
    virtual float getAngle() const = 0;
    
    virtual ~Polygon() noexcept = default;
    Polygon(const Polygon&) noexcept = default;
    Polygon& operator=(const Polygon&) noexcept = default;
    Polygon(Polygon&&) noexcept = default;
    Polygon& operator=(Polygon&&) noexcept = default;
protected:
    explicit Polygon() { }
};