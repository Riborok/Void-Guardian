#pragma once

#include "../geometry/GeomAuxiliaryFunc.h"
#include "../model/polygon/Polygon.h"

class RectangularCoverage : public Polygon {
protected:
    sf::Vector2f _points[NUM_POINTS_FOR_QUAD];
public:
    RectangularCoverage (const float x_start, const float y_start, const float x_last, const float y_last) {
        _points[0] = sf::Vector2f(x_start, y_start);
        _points[1] = sf::Vector2f(x_last, y_start);
        _points[2] = sf::Vector2f(x_last, y_last);
        _points[3] = sf::Vector2f(x_start, y_last);
    }

    size_t pointsAmount() const override { return NUM_POINTS_FOR_QUAD; }
    sf::Vector2f *points() override { return _points; }
    const sf::Vector2f calcCenter() const override { return CALC_MIDPOINT(_points[0], _points[2]); }
    float getRotation() const override { return 0; }
    float getBoundingRectangleWidth() const override { return GeomAuxiliaryFunc::calcDistance(_points[0], _points[1]); }
    float getBoundingRectangleHeight() const override { return GeomAuxiliaryFunc::calcDistance(_points[0], _points[3]); }

    ~RectangularCoverage() noexcept override = default;
    RectangularCoverage& operator=(RectangularCoverage&&) noexcept = default;
    RectangularCoverage(RectangularCoverage&&) noexcept = default;
    
    RectangularCoverage(const RectangularCoverage&) noexcept = delete;
    RectangularCoverage& operator=(const RectangularCoverage&) noexcept = delete;
};
