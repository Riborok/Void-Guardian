#pragma once

#include <SFML/System/Vector2.hpp>

class Polygon {
protected:
    std::vector<sf::Vector2f> _points;
public:
    /**
    * Returns the vector of points that define the shape.
    * @return The vector of points defining the shape.
    */
    std::vector<sf::Vector2f> &points() { return _points; }


    /**
     * Calculates and returns the center point of the shape.
     * @return The center point of the shape.
     */
    virtual const sf::Vector2f calcCenter() const = 0;
    
    /**
     * Get the rotation angle in radians.
     * @return The rotation angle in radians.
     */
    virtual float getRotation() const = 0;

    /**
     * Gets the height of the bounding rectangle that encompasses the polygon.
     * @return The height of the bounding rectangle.
     */
    virtual float getBoundingRectangleHeight() const = 0;

    /**
     * Gets the width of the bounding rectangle that encompasses the polygon.
     * @return The width of the bounding rectangle.
     */
    virtual float getBoundingRectangleWidth() const = 0;
    
    virtual ~Polygon() noexcept = default;
    Polygon& operator=(Polygon&&) noexcept = default;
    Polygon(Polygon&&) noexcept = default;
    
    Polygon(const Polygon&) noexcept = delete;
    Polygon& operator=(const Polygon&) noexcept = delete;
protected:
    explicit Polygon(std::vector<sf::Vector2f> &&points): _points(std::move(points)) { }
};