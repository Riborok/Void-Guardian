#pragma once

#include "Axis.hpp"
#include "ColisAuxiliaryTools.hpp"
#include "CollisionResult.hpp"
#include "../../model/polygon/Polygon.hpp"

namespace CollisionDetection {
    /**
     * Calculates the extended projection of a polygon onto a specified axis.
     * @param polygon The polygon to project.
     * @param axis The axis onto which the projection is calculated.
     * @param calculate_mid_point If true, calculates the midpoint of the projection
     * when the projection is nearly identical.
     * @param result Reference to the ExtendedProjection struct to store the result.
     */
    void getExtendedProjection(const Polygon &polygon, const sf::Vector2f &axis,
        const bool calculate_mid_point, ExtendedProjection &result);

    /**
     * Calculates the standard projection of a polygon onto a specified axis.
     * @param polygon The polygon to project.
     * @param axis The axis onto which the projection is calculated.
     * @param result Reference to the Projection struct to store the result.
     */
    void getProjection(const Polygon &polygon, const sf::Vector2f &axis, Projection &result);
 
    /**
     * Calculates the axes for a given polygon using its points.
     * These axes are used for collision detection using the Separating Axis Theorem (SAT).
     * @param polygon The polygon for which to calculate the axes.
     * @param axes A vector where the calculated axes representing the edges of the polygon will be stored.
     */
    void getAxes(const Polygon &polygon, Axes &axes);

    /**
     * Calculates the collision result between two polygons using the Separating Axis Theorem (SAT).
     * @param polygon1 The first polygon to calculate collision result for.
     * @param polygon2 The second polygon to calculate collision result for.
     * @param result The `CollisionResult` object to store the collision result if a collision occurred.
     * @return `true` if a collision occurred and the result is stored in `result`, `false` if there's no collision, and `result` is not modified.
     */
    bool getCollisionResult(const Polygon &polygon1, const Polygon &polygon2, CollisionResult &result);

    /**
     * Checks if two polygons intersect using the Separating Axis Theorem (SAT).
     * @param polygon1 The first polygon to check for intersection.
     * @param polygon2 The second polygon to check for intersection.
     * @param axes1 The axes for the first polygon.
     * @param axes2 The axes for the second polygon.
     * @returns `true` if the two polygons intersect, `false` otherwise.
     */
    bool hasCollision(const Polygon &polygon1, const Polygon &polygon2, const Axes &axes1, const Axes &axes2);
}