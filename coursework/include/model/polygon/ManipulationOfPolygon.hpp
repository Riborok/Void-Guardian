#pragma once

#include "Polygon.hpp"

namespace ManipulationOfPolygon {
    /**
     * Move a polygon by a specified vector.
     * @param polygon The polygon to move.
     * @param vector The vector representing the movement.
     */
    void movePolygon(Polygon &polygon, const sf::Vector2f &vector);

    /**
     * Rotate a polygon by a specified angle (in radians) around its center point.
     * @param polygon The polygon to rotate.
     * @param delta_angle The angle (in radians) by which to rotate the polygon.
     */
    void rotatePolygon(Polygon &polygon, const float delta_angle);
}