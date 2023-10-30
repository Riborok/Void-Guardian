#pragma once
#include "Polygon.h"
#include "../../geometry/Trigonometry.h"
#include "../../geometry/Vector2Rotation.h"

namespace ManipulationOfPolygon {
    /**
     * Move a polygon by a specified vector.
     * @param polygon The polygon to move.
     * @param vector The vector representing the movement.
     */
    inline void movePolygon(Polygon &polygon, const sf::Vector2f &vector) {
        sf::Vector2f *points = polygon.points();
        const size_t amount = polygon.pointsAmount();
        for (size_t i = 0; i < amount; ++i)
            points[i] += vector;
    }

    /**
     * Rotate a polygon by a specified angle (in radians) around its center point.
     * @param polygon The polygon to rotate.
     * @param delta_angle The angle (in radians) by which to rotate the polygon.
     */
    inline void rotatePolygon(Polygon &polygon, const float delta_angle) {
        const float sin = Trigonometry::sinDegrees(delta_angle);
        const float cos = Trigonometry::cosDegrees(delta_angle);
        const sf::Vector2f center = polygon.calcCenter();

        sf::Vector2f *points = polygon.points();
        const size_t amount = polygon.pointsAmount();
        for (size_t i = 0; i < amount; ++i)
            Vector2Rotation::rotateVector2AroundTarget(points[i], center, sin, cos);
    }
}