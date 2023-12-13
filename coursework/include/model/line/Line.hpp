#pragma once
#include "../polygon/Polygon.hpp"

class Line final : public Polygon {
public:
    Line(const sf::Vector2f &p0, const sf::Vector2f &p1);
    
    [[nodiscard]] const sf::Vector2f calcCenter() const override;
    [[nodiscard]] float getRotation() const override;
    
    ~Line() noexcept override = default;
    Line(Line&&) noexcept = delete;
    Line& operator=(Line&&) noexcept = delete;
    Line(const Line&) noexcept = delete;
    Line& operator=(const Line&) noexcept = delete;
};