#pragma once

#include "ManipulationOfEntity.h"
#include "Entity.h"
#include "../../geometry/GeomAuxiliaryFunc.h"

#define POINTS_AMOUNT 4  // NOLINT(modernize-macro-to-enum)

class RectangularEntity final : public Entity {
    sf::Vector2f _points[POINTS_AMOUNT];
public:
    RectangularEntity(const sf::Vector2f &point, const float width, const float height, const float angle, const int id)
        : Entity(id) {
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
    RectangularEntity(const RectangularEntity&) noexcept = default;
    RectangularEntity& operator=(const RectangularEntity&) noexcept = default;
    RectangularEntity(RectangularEntity&&) noexcept = default;
    RectangularEntity& operator=(RectangularEntity&&) noexcept = default;

    const size_t &pointsAmount() const override { return POINTS_AMOUNT; }
    sf::Vector2f *points() override { return _points; }
    const sf::Vector2f calcCenter() const override { return CALC_MIDPOINT(_points[0], _points[2]); }
    float getAngle() const override { return std::atan2(_points[1].y - _points[0].y, _points[1].x - _points[0].x); }
};