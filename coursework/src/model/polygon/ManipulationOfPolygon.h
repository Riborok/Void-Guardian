#pragma once
#include "Polygon.h"
#include "../../geometry/Trigonometry.h"
#include "../../geometry/Vector2Rotation.h"

namespace ManipulationOfPolygon {
    inline void movePolygon(Polygon &polygon, const sf::Vector2f &vector) {
        sf::Vector2f *points = polygon.points();
        const size_t &amount = polygon.pointsAmount();
        for (size_t i = 0; i < amount; ++i)
            points[i] += vector;
    }

    inline void rotatePolygon(Polygon &polygon, const float delta_angle) {
        const float sin = SIN_DEGREES(delta_angle);
        const float cos = COS_DEGREES(delta_angle);
        const sf::Vector2f center = polygon.calcCenter();

        sf::Vector2f *points = polygon.points();
        const size_t &amount = polygon.pointsAmount();
        for (size_t i = 0; i < amount; ++i)
            Vector2Rotation::rotateVector2AroundTarget(points[i], center, sin, cos);
    }
}