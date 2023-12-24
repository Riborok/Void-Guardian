#include "../../../include/model/line/Line.hpp"

#include "../../../include/geometry/GeomAuxiliaryFunc.hpp"

Line::Line(const sf::Vector2f& p0, const sf::Vector2f& p1): Polygon(std::vector{p0, p1}) { }

const sf::Vector2f Line::calcCenter() const {
    return GeomAuxiliaryFunc::calcMidpoint(_points[0], _points[1]);
}

float Line::getRotation() const {
    return GeomAuxiliaryFunc::calcAngle(_points[1] - _points[0]);
}

float Line::getBoundingRectWidth() const {
    return GeomAuxiliaryFunc::calcDistance(_points[0], _points[1]);
}

float Line::getBoundingRectHeight() const {
    return 0;
}