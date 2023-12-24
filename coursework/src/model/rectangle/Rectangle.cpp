#include <cmath>

#include "../../../include/model/rectangle/Rectangle.hpp"
#include "../../../include/geometry/GeomAuxiliaryFunc.hpp"
#include "../../../include/geometry/Trigonometry.hpp"

Rectangle::Rectangle(const RotatedRectangleData &data):
    Polygon {
        std::vector{
            sf::Vector2f(data.p0),
            sf::Vector2f(data.p0.x + data.size.x, data.p0.y),
            sf::Vector2f(data.p0.x + data.size.x, data.p0.y + data.size.y),
            sf::Vector2f(data.p0.x, data.p0.y + data.size.y)
        }
    } {
    if (std::abs(data.angle) > Trigonometry::EPSILON_RADIANS) { rotate(_points[0], data.angle); }
}

Rectangle::Rectangle(const AlignedRectangleData &data) :
    Polygon{
        std::vector{
            sf::Vector2f(data.x0, data.y0),
            sf::Vector2f(data.x1, data.y0),
            sf::Vector2f(data.x1, data.y1),
            sf::Vector2f(data.x0, data.y1)
        }
    } { }

Rectangle::Rectangle(const sf::Vector2f &focus, const sf::Vector2f &half_size):
    Rectangle({focus.x - half_size.x,
        focus.y - half_size.y,
        focus.x + half_size.x,
        focus.y + half_size.y}) { } 

const sf::Vector2f Rectangle::calcCenter() const {
    return GeomAuxiliaryFunc::calcMidpoint(_points[0], _points[2]);
}

float Rectangle::getRotation() const {
    return GeomAuxiliaryFunc::calcAngle(_points[1] - _points[0]);
}

float Rectangle::getBoundingRectWidth() const {
    return GeomAuxiliaryFunc::calcDistance(_points[0], _points[1]);
}

float Rectangle::getBoundingRectHeight() const {
    return GeomAuxiliaryFunc::calcDistance(_points[0], _points[3]);
}