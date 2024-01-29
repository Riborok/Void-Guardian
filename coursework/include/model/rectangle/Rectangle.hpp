#pragma once
#include "RectangleInfo.hpp"
#include "../polygon/Polygon.hpp"

class Rectangle : public Polygon {
public:
    explicit Rectangle(const RotatedRectangleInfo &rotated_rect_info);
    explicit Rectangle(const AlignedRectangleInfo &aligned_rect_info);
    Rectangle(const sf::Vector2f &focus, const sf::Vector2f &half_size);

    [[nodiscard]] const sf::Vector2f calcCenter() const override;
    [[nodiscard]] float getRotation() const override;
    [[nodiscard]] float getBoundingRectWidth() const override;
    [[nodiscard]] float getBoundingRectHeight() const override;
    
    ~Rectangle() noexcept override = default;
    Rectangle(Rectangle&&) noexcept = default;
    Rectangle& operator=(Rectangle&&) noexcept = delete;
    
    Rectangle(const Rectangle&) noexcept = delete;
    Rectangle& operator=(const Rectangle&) noexcept = delete;
};
