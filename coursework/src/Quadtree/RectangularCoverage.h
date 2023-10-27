#pragma once

#define POINTS_AMOUNT 4  // NOLINT(modernize-macro-to-enum)
#include "../geometry/GeomAuxiliaryFunc.h"
#include "../model/polygon/Polygon.h"

class RectangularCoverage : public Polygon {
protected:
    sf::Vector2f _points[POINTS_AMOUNT];
public:
    RectangularCoverage (const float x_start, const float y_start, const float x_last, const float y_last) {
        _points[0] = sf::Vector2f(x_start, y_start);
        _points[1] = sf::Vector2f(x_last, y_start);
        _points[2] = sf::Vector2f(x_last, y_last);
        _points[3] = sf::Vector2f(x_start, y_last);
    }

    const size_t &pointsAmount() const override { return POINTS_AMOUNT; }
    sf::Vector2f *points() override { return _points; }
    const sf::Vector2f calcCenter() const override { return CALC_MIDPOINT(_points[0], _points[2]); }
    float getRotation() const override { return 0; }

    virtual ~RectangularCoverage() noexcept override = default;
    RectangularCoverage(const RectangularCoverage&) noexcept = default;
    RectangularCoverage& operator=(const RectangularCoverage&) noexcept = default;
    RectangularCoverage(RectangularCoverage&&) noexcept = default;
    RectangularCoverage& operator=(RectangularCoverage&&) noexcept = default;
};
