#include <cmath>

#include "../../../include/model/rectangle/Rectangle.hpp"
#include "../../../include/geometry/GeomAuxiliaryFunc.hpp"
#include "../../../include/geometry/Trigonometry.hpp"

Rectangle::Rectangle(const RotatedRectangleInfo &rotated_rect_info):
    Polygon {
        std::vector{
            sf::Vector2f(rotated_rect_info.p0),
            sf::Vector2f(rotated_rect_info.p0.x + rotated_rect_info.size.x, rotated_rect_info.p0.y),
            sf::Vector2f(rotated_rect_info.p0.x + rotated_rect_info.size.x, rotated_rect_info.p0.y + rotated_rect_info.size.y),
            sf::Vector2f(rotated_rect_info.p0.x, rotated_rect_info.p0.y + rotated_rect_info.size.y)
        }
    } {
    if (std::abs(rotated_rect_info.angle) > Trigonometry::EPSILON_RADIANS) { rotate(_points[0], rotated_rect_info.angle); }
}

Rectangle::Rectangle(const AlignedRectangleInfo &aligned_rect_info) :
    Polygon{
        std::vector{
            sf::Vector2f(aligned_rect_info.x0, aligned_rect_info.y0),
            sf::Vector2f(aligned_rect_info.x1, aligned_rect_info.y0),
            sf::Vector2f(aligned_rect_info.x1, aligned_rect_info.y1),
            sf::Vector2f(aligned_rect_info.x0, aligned_rect_info.y1)
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