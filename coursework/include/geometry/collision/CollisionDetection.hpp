#pragma once

#include <vector>

#include "Axis.hpp"
#include "../../additionally/Types.hpp"
#include "../../model/polygon/Polygon.hpp"

namespace CollisionDetection {
    /**
     * Calculates the axes for a given polygon using its points.
     * These axes are used for collision detection using the Separating Axis Theorem (SAT).
     * @param polygon The polygon for which to calculate the axes.
     * @param axes A vector where the calculated axes representing the edges of the polygon will be stored.
     */
    void getAxes(Polygon &polygon, std::vector<Axis> &axes);

    /**
     * Calculates the collision result between two polygons using the Separating Axis Theorem (SAT).
     * @param polygon1 The first polygon to calculate collision result for.
     * @param polygon2 The second polygon to calculate collision result for.
     * @param result The `CollisionResult` object to store the collision result if a collision occurred.
     * @return `true` if a collision occurred and the result is stored in `result`, `false` if there's no collision, and `result` is not modified.
     */
    bool getCollisionResult(Polygon &polygon1, Polygon &polygon2, Types::CollisionResult &result);

    /**
     * Checks if two polygons intersect using the Separating Axis Theorem (SAT).
     * @param polygon1 The first polygon to check for intersection.
     * @param polygon2 The second polygon to check for intersection.
     * @param axes1 The axes for the first polygon.
     * @param axes2 The axes for the second polygon.
     * @returns `true` if the two polygons intersect, `false` otherwise.
     */
    bool hasCollision(Polygon &polygon1, Polygon &polygon2, const std::vector<Axis> &axes1, const std::vector<Axis> &axes2);
}