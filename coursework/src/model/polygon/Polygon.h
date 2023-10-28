#pragma once

#include <SFML/System/Vector2.hpp>

#define NUM_POINTS_FOR_QUAD 4 // NOLINT(modernize-macro-to-enum)

class Polygon {
public:
    virtual const size_t &pointsAmount() const = 0;
    virtual sf::Vector2f *points() = 0;
    virtual const sf::Vector2f calcCenter() const = 0;
    virtual float getRotation() const = 0;
    
    virtual ~Polygon() noexcept = default;
    
    Polygon(const Polygon&) noexcept = delete;
    Polygon& operator=(const Polygon&) noexcept = delete;
    Polygon(Polygon&&) noexcept = delete;
    Polygon& operator=(Polygon&&) noexcept = delete;
protected:
    explicit Polygon() { }
};