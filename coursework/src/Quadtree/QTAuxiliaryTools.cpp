#include "../../include/Quadtree/QTAuxiliaryTools.hpp"

Boundary::Boundary(const AlignedRectangleData &data)
    : Rectangle(data), _axes{
        Axis(_points[0], _points[1]),
        Axis(_points[1], _points[2]),
        Axis(_points[2], _points[3]),
        Axis(_points[3], _points[0])
    } { }

const std::vector<Axis> &Boundary::getAxes() const {
    return _axes;
}
