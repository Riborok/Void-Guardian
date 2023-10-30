#pragma once

#include "RectangularCoverage.h"
#include "../geometry/collision/Axis.h"

class Boundary final : public RectangularCoverage {
    std::vector<Axis> _axes;
public:
    Boundary(const float x_start, const float y_start, const float x_last, const float y_last):
        RectangularCoverage(x_start, y_start, x_last, y_last), _axes{
            Axis(_points[0], _points[1]),
            Axis(_points[1], _points[2]),
            Axis(_points[2], _points[3]),
            Axis(_points[3], _points[0])
        } { }
    std::vector<Axis> &getAxes() { return _axes; }

    ~Boundary() noexcept override = default;
    Boundary& operator=(Boundary&&) noexcept = default;
    Boundary(Boundary&&) noexcept = default;
        
    Boundary(const Boundary&) noexcept = delete;
    Boundary& operator=(const Boundary&) noexcept = delete;
};