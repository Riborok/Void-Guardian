#include "../../include/Quadtree/QTAuxiliaryTools.hpp"

Boundary::Boundary(const float x_start, const float y_start, const float x_last, const float y_last)
    : Rectangle(x_start, y_start, x_last, y_last), _axes{
        Axis(_points[0], _points[1]),
        Axis(_points[1], _points[2]),
        Axis(_points[2], _points[3]),
        Axis(_points[3], _points[0])
    } { }

const std::vector<Axis> &Boundary::getAxes() const {
    return _axes;
}
