#pragma once
#include "Polygon.hpp"
#include "../../additionally/Types.hpp"
#include "../../additionally/other types/InitializationData.hpp"

class Rectangle : public Polygon {
public:
    explicit Rectangle(const RotatedRectangleData &data);
    explicit Rectangle(const AlignedRectangleData &data);
    Rectangle(const sf::Vector2f &focus, const sf::Vector2f &half_size);
    
    ~Rectangle() noexcept override = default;
    Rectangle(Rectangle&&) noexcept = default;
    Rectangle& operator=(Rectangle&&) noexcept = default;
    
    Rectangle(const Rectangle&) noexcept = delete;
    Rectangle& operator=(const Rectangle&) noexcept = delete;

    [[nodiscard]] const sf::Vector2f calcCenter() const override;
    [[nodiscard]] float getRotation() const override;
};
