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
        for (auto &point : polygon.points())
            point += vector;
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
        
        for (auto &point : polygon.points())
            Vector2Rotation::rotateVector2AroundTarget(point, center, sin, cos);
    }
}