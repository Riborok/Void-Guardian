#pragma once

#include <SFML/System/Vector2.hpp>

class Polygon {
protected:
    enum : int { NUM_POINTS_FOR_QUAD = 4 };
public:
    virtual size_t pointsAmount() const = 0;
    virtual sf::Vector2f *points() = 0;
    virtual const sf::Vector2f calcCenter() const = 0;
    
    /**
     * Get the rotation angle in radians.
     * @return The rotation angle in radians.
     */
    virtual float getRotation() const = 0;
    
    virtual ~Polygon() noexcept = default;
    Polygon& operator=(Polygon&&) noexcept = default;
    Polygon(Polygon&&) noexcept = default;
    
    Polygon(const Polygon&) noexcept = delete;
    Polygon& operator=(const Polygon&) noexcept = delete;
protected:
    explicit Polygon() { }
};