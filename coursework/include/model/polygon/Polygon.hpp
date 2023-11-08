#pragma once

#include <vector>
#include <SFML/System/Vector2.hpp>

class Polygon {
protected:
    std::vector<sf::Vector2f> _points;
public:
    /**
    * Returns the vector of points that define the shape.
    * @return The vector of points defining the shape.
    */
    [[nodiscard]] const std::vector<sf::Vector2f> &getPoints() const;

    /**
     * Moves all points of the shape by the specified vector.
     * @param vector The vector by which to move all points.
     */
    void move(const sf::Vector2f &vector);

    /**
    * Rotates all points of the shape around the specified target point by the given angle.
    * @param target The point around which the shape is rotated.
    * @param delta_angle The angle (in degrees) by which to rotate the shape.
    */
    void rotate(const sf::Vector2f &target, const float delta_angle);
    
    /**
     * Calculates and returns the center point of the shape.
     * @return The center point of the shape.
     */
    [[nodiscard]] virtual const sf::Vector2f calcCenter() const = 0;
    
    /**
     * Get the rotation angle in radians.
     * @return The rotation angle in radians.
     */
    [[nodiscard]] virtual float getRotation() const = 0;

    /**
     * Gets the height of the bounding rectangle that encompasses the polygon.
     * @return The height of the bounding rectangle.
     */
    [[nodiscard]] virtual float getBoundingRectangleHeight() const = 0;

    /**
     * Gets the width of the bounding rectangle that encompasses the polygon.
     * @return The width of the bounding rectangle.
     */
    [[nodiscard]] virtual float getBoundingRectangleWidth() const = 0;
    
    virtual ~Polygon() noexcept = default;
    Polygon& operator=(Polygon&&) noexcept = default;
    Polygon(Polygon&&) noexcept = default;
    
    Polygon(const Polygon&) noexcept = delete;
    Polygon& operator=(const Polygon&) noexcept = delete;
protected:
    explicit Polygon(std::vector<sf::Vector2f> &&points);
};