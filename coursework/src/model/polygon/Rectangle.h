#pragma once
#include "ManipulationOfPolygon.h"
#include "Polygon.h"
#include "../../geometry/GeomAuxiliaryFunc.h"

class Rectangle : public Polygon {
protected:
    sf::Vector2f _points[NUM_POINTS_FOR_QUAD];
public:
    Rectangle(const sf::Vector2f &point, const float width, const float height, const float angle):
    _points{
        sf::Vector2f(point),
        sf::Vector2f(point.x + width, point.y),
        sf::Vector2f(point.x + width, point.y + height),
        sf::Vector2f(point.x, point.y + height)
    } {
        ManipulationOfPolygon::rotatePolygon(*this, angle);
    }

    Rectangle(const float x_start, const float y_start, const float x_last, const float y_last) :
    _points {
        sf::Vector2f(x_start, y_start),
        sf::Vector2f(x_last, y_start),
        sf::Vector2f(x_last, y_last),
        sf::Vector2f(x_start, y_last)
    } { }

    Rectangle(const sf::Vector2f &focus, const sf::Vector2f &half_size):
        Rectangle(focus.x - half_size.x,
            focus.y - half_size.y,
            focus.x + half_size.x,
            focus.y + half_size.y) { } 
    
    ~Rectangle() noexcept override = default;
    Rectangle(Rectangle&&) noexcept = default;
    Rectangle& operator=(Rectangle&&) noexcept = default;
    
    Rectangle(const Rectangle&) noexcept = delete;
    Rectangle& operator=(const Rectangle&) noexcept = delete;

    size_t pointsAmount() const override { return NUM_POINTS_FOR_QUAD; }
    sf::Vector2f *points() override { return _points; }
    const sf::Vector2f calcCenter() const override { return GeomAuxiliaryFunc::calcMidpoint(_points[0], _points[2]); }
    float getRotation() const override { return std::atan2(_points[1].y - _points[0].y, _points[1].x - _points[0].x); }
    float getBoundingRectangleWidth() const override { return GeomAuxiliaryFunc::calcDistance(_points[0], _points[1]); }
    float getBoundingRectangleHeight() const override { return GeomAuxiliaryFunc::calcDistance(_points[0], _points[3]); }
};
