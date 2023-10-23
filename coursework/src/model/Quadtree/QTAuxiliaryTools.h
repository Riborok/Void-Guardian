#pragma once
#include <type_traits>

#include "RectangularCoverage.h"
#include "../../geometry/collision/Axis.h"
#include "../polygon/IdPolygon.h"

class Boundary final : public RectangularCoverage {
    std::vector<Axis> _axes;
public:
    Boundary(const float x_start, const float y_start, const float x_last, const float y_last):
        RectangularCoverage(x_start, y_start, x_last, y_last){
        _axes.emplace_back(_points[0], _points[1]);
        _axes.emplace_back(_points[1], _points[2]);
        _axes.emplace_back(_points[2], _points[3]);
        _axes.emplace_back(_points[3], _points[0]);
    }
    std::vector<Axis> &GetAxes() { return _axes; }

    ~Boundary() noexcept override = default;
    Boundary(const Boundary&) noexcept = default;
    Boundary& operator=(const Boundary&) noexcept = default;
    Boundary(Boundary&&) noexcept = default;
    Boundary& operator=(Boundary&&) noexcept = default;
};

template <typename T>
using EnableIfIdPolygon = std::enable_if_t<std::is_base_of_v<IdPolygon, T>>;