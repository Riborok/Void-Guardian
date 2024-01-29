#pragma once
#include "../../game/construction/game field creation/MinMaxPoint.hpp"

struct AlignedRectangleInfo final {
    float x0;
    float y0;
    float x1;
    float y1;
    AlignedRectangleInfo(const float x0, const float y0, const float x1, const float y1) :
        x0(x0), y0(y0), x1(x1), y1(y1) { }
    explicit AlignedRectangleInfo(const MinMaxPoint &min_max_point) :
        x0(static_cast<float>(min_max_point.first.x)), y0(static_cast<float>(min_max_point.first.y)),
        x1(static_cast<float>(min_max_point.second.x)), y1(static_cast<float>(min_max_point.second.y)) { }
};

struct RotatedRectangleInfo final {
    sf::Vector2f p0;
    sf::Vector2f size;
    float angle;
    RotatedRectangleInfo(const sf::Vector2f& p0, const sf::Vector2f& size, const float angle)
        : p0(p0), size(size), angle(angle) { }
};
