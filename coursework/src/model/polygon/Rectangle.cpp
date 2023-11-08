#include <cmath>

#include "../../../include/model/polygon/Rectangle.hpp"

#include "../../../include/geometry/GeomAuxiliaryFunc.hpp"

Rectangle::Rectangle(const sf::Vector2f &point, const float width, const float height, const float angle):
    Polygon {
            std::vector{
                sf::Vector2f(point),
                sf::Vector2f(point.x + width, point.y),
                sf::Vector2f(point.x + width, point.y + height),
                sf::Vector2f(point.x, point.y + height)
            }
    } {
    rotate(Rectangle::calcCenter(), angle);
}

Rectangle::Rectangle(const float x_start, const float y_start, const float x_last, const float y_last) :
    Polygon{
            std::vector{
                sf::Vector2f(x_start, y_start),
                sf::Vector2f(x_last, y_start),
                sf::Vector2f(x_last, y_last),
                sf::Vector2f(x_start, y_last)
            }
    } { }

Rectangle::Rectangle(const sf::Vector2f &focus, const sf::Vector2f &half_size):
    Rectangle(focus.x - half_size.x,
        focus.y - half_size.y,
        focus.x + half_size.x,
        focus.y + half_size.y) { } 

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
