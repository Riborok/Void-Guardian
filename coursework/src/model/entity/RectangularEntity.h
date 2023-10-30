#pragma once

#include "ManipulationOfEntity.h"
#include "Entity.h"
#include "../../geometry/GeomAuxiliaryFunc.h"

class RectangularEntity final : public Entity {
    sf::Vector2f _points[NUM_POINTS_FOR_QUAD];
public:
    RectangularEntity(const sf::Vector2f &point, const float width, const float height, const float angle) {
        adjustPolygon(point, width, height, angle);
    }
    void adjustPolygon(const sf::Vector2f &point, const float width, const float height, const float angle) {
        _points[0] = sf::Vector2f(point);
        _points[1] = sf::Vector2f(point.x + width, point.y);
        _points[2] = sf::Vector2f(point.x + width, point.y + height);
        _points[3] = sf::Vector2f(point.x, point.y + height);

        ManipulationOfEntity::rotateEntity(*this, angle);
    }
    ~RectangularEntity() noexcept override = default;
    
    RectangularEntity(const RectangularEntity&) noexcept = delete;
    RectangularEntity& operator=(const RectangularEntity&) noexcept = delete;
    RectangularEntity(RectangularEntity&&) noexcept = delete;
    RectangularEntity& operator=(RectangularEntity&&) noexcept = delete;

    size_t pointsAmount() const override { return NUM_POINTS_FOR_QUAD; }
    sf::Vector2f *points() override { return _points; }
    const sf::Vector2f calcCenter() const override { return GeomAuxiliaryFunc::calcMidpoint(_points[0], _points[2]); }
    float getRotation() const override { return std::atan2(_points[1].y - _points[0].y, _points[1].x - _points[0].x); }

    float getBoundingRectangleWidth() const override { return GeomAuxiliaryFunc::calcDistance(_points[0], _points[1]); }
    float getBoundingRectangleHeight() const override { return GeomAuxiliaryFunc::calcDistance(_points[0], _points[3]); }
};