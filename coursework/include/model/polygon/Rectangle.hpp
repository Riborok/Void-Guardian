#pragma once
#include "Polygon.hpp"

class Rectangle : public Polygon {
public:
    Rectangle(const sf::Vector2f &point, const float width, const float height, const float angle);
    Rectangle(const float x_start, const float y_start, const float x_last, const float y_last);
    Rectangle(const sf::Vector2f &focus, const sf::Vector2f &half_size);
    
    ~Rectangle() noexcept override = default;
    Rectangle(Rectangle&&) noexcept = default;
    Rectangle& operator=(Rectangle&&) noexcept = default;
    
    Rectangle(const Rectangle&) noexcept = delete;
    Rectangle& operator=(const Rectangle&) noexcept = delete;

    [[nodiscard]] const sf::Vector2f calcCenter() const override;
    [[nodiscard]] float getRotation() const override;
    [[nodiscard]] float getBoundingRectangleWidth() const override;
    [[nodiscard]] float getBoundingRectangleHeight() const override;
};