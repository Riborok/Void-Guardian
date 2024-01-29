#include "../../include/quadtree/QTAuxiliaryTools.hpp"

Boundary::Boundary(const AlignedRectangleInfo &aligned_rect_info)
    : Rectangle(aligned_rect_info), _axes{
        Axis(_points[0], _points[1]),
        Axis(_points[1], _points[2]),
        Axis(_points[2], _points[3]),
        Axis(_points[3], _points[0])
    } { }

const Axes &Boundary::getAxes() const {
    return _axes;
}
