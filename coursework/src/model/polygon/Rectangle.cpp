#include <cmath>

#include "../../../include/model/polygon/Rectangle.hpp"

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
    if (std::abs(data.angle) > Trigonometry::EPSILON_DEGREES) { rotate(Rectangle::calcCenter(), data.angle); }
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
    return std::atan2(_points[1].y - _points[0].y, _points[1].x - _points[0].x);
}

float Rectangle::getBoundingRectangleWidth() const {
    return GeomAuxiliaryFunc::calcDistance(_points[0], _points[1]);
}

float Rectangle::getBoundingRectangleHeight() const {
    return GeomAuxiliaryFunc::calcDistance(_points[0], _points[3]);
}
