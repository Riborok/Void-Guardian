#pragma once

#include <vector>

#include <cmath>
#include <corecrt_math_defines.h>

#include "ColisAuxiliaryTools.h"
#include "Axis.h"
#include "../GeomAuxiliaryFunc.h"
#include "../../additionally/Types.h"
#include "../../model/polygon/Polygon.h"

#define EPSILON 1 // NOLINT(modernize-macro-to-enum)

namespace CollisionDetection {
    namespace InnerLogic {
        
        struct CollisionResultHelper {
            float smallest_overlap = FLT_MAX;
            const Axis *collision_axis = nullptr;
            bool is_polygon1_axis = false;
        };
        
        inline void GetProjection(Polygon &polygon, const sf::Vector2f &axis, Projection &result) {
            const sf::Vector2f *points = polygon.Points();
            const size_t &amount = polygon.PointsAmount();
    
            float min = DOT_PRODUCT(axis, points[0]);
            float max = min;

            for (size_t i = 1; i < amount; ++i) {
                const float dot_product_result = DOT_PRODUCT(axis, points[i]);
                if (dot_product_result < min) {
                    min = dot_product_result;
                }
                else if (dot_product_result > max) {
                    max = dot_product_result;
                }
            }

            result = { min, max };
        }

        inline void GetExtendedProjection(Polygon &polygon, const sf::Vector2f &axis, const bool calculate_mid_point, ExtendedProjection &result) {
            const sf::Vector2f *points = polygon.Points();
            const size_t &amount = polygon.PointsAmount();

            float min = DOT_PRODUCT(axis, points[0]);
            float max = min;
            sf::Vector2f min_point = points[0];
            sf::Vector2f max_point = points[0];

            for (size_t i = 1; i < amount; ++i) {
                const float dot_product_result = DOT_PRODUCT(axis, points[i]);

                if (dot_product_result < min) {
                    min = dot_product_result;
                    min_point = points[i];
                }
                else if (dot_product_result > max) {
                    max = dot_product_result;
                    max_point = points[i];
                }
                else if (calculate_mid_point && std::abs(dot_product_result - min) < EPSILON) {
                    min_point = CALC_MIDPOINT(min_point, points[i]);
                }
                else if (calculate_mid_point && std::abs(dot_product_result - max) < EPSILON) {
                    max_point = CALC_MIDPOINT(max_point, points[i]);
                }
            }

            result = { min, max, min_point, max_point };
        }

        inline bool AreProjectionsOverlapping(const std::vector<Axis> &axes, Polygon &polygon1, Polygon &polygon2) {
            for (const Axis &axis : axes) {
                Projection projection1;
                GetProjection(polygon1, axis, projection1);
                Projection projection2;
                GetProjection(polygon2, axis, projection2);

                if (std::min(projection1.max - projection2.min, projection2.max - projection1.min) <= 0) {
                    return false;
                }
            }
            return true;
        }

        inline bool IsSmallestOverlapAxisFound(const std::vector<Axis> &axes, const bool is_axes1, Polygon &polygon1, Polygon &polygon2, CollisionResultHelper &collision_result_help) {
            for (const auto &axis : axes) {
                Projection projection1;
                GetProjection(polygon1, axis, projection1);
                Projection projection2;
                GetProjection(polygon2, axis, projection2);

                const float overlap = std::min(projection1.max - projection2.min, projection2.max - projection1.min);

                if (overlap <= 0.0f)
                    return false;

                if (overlap < collision_result_help.smallest_overlap) {
                    collision_result_help.smallest_overlap = overlap;
                    collision_result_help.collision_axis = &axis;
                    collision_result_help.is_polygon1_axis = is_axes1;
                }
            }
            return true;
        }

        inline void FindClosestVertex(Polygon &polygon1, Polygon &polygon2, const Axis &axis, const bool is_polygon1_axis, sf::Vector2f &result) {
            Projection projection;
            ExtendedProjection extended_projection;

            if (is_polygon1_axis && !ARE_ORTHOGONAL(polygon1.GetAngle(), polygon2.GetAngle())) {
                GetProjection(polygon1, axis, projection);
                GetExtendedProjection(polygon2, axis, false, extended_projection);
            }
            else {
                GetProjection(polygon2, axis, projection);
                GetExtendedProjection(polygon1, axis, true, extended_projection);
            }

            result = extended_projection.max - projection.min < projection.max - extended_projection.min
                ? extended_projection.max_point
                : extended_projection.min_point;
        }
    }

    /**
     * Calculates the axes for a given polygon using its points.
     * These axes are used for collision detection using the Separating Axis Theorem (SAT).
     * @param polygon The polygon for which to calculate the axes.
     * @param axes A vector where the calculated axes representing the edges of the polygon will be stored.
     */
    inline void GetAxes(Polygon &polygon, std::vector<Axis> &axes) {
        const sf::Vector2f *points = polygon.Points();
        const size_t last_index = polygon.PointsAmount() - 1;

        for (size_t i = 0; i < last_index; i++) {
            axes.emplace_back(points[i], points[i + 1]);
        }
        axes.emplace_back(points[last_index], points[0]);
    }

    /**
     * Calculates the collision result between two polygons using the Separating Axis Theorem (SAT).
     * @param polygon1 The first polygon to calculate collision result for.
     * @param polygon2 The second polygon to calculate collision result for.
     * @param result The `CollisionResult` object to store the collision result if a collision occurred.
     * @return `true` if a collision occurred and the result is stored in `result`, `false` if there's no collision, and `result` is not modified.
     */
    inline bool GetCollisionResult(Polygon &polygon1, Polygon &polygon2, Types::CollisionResult &result) {
        std::vector<Axis> axes1;
        std::vector<Axis> axes2;
        GetAxes(polygon1, axes1);
        GetAxes(polygon2, axes2);

        InnerLogic::CollisionResultHelper collision_result_help;

        if (!IsSmallestOverlapAxisFound(axes1, true, polygon1, polygon2, collision_result_help) ||
                !IsSmallestOverlapAxisFound(axes2, false, polygon1, polygon2, collision_result_help))
            return false;

        InnerLogic::FindClosestVertex(polygon1, polygon2, *collision_result_help.collision_axis, collision_result_help.is_polygon1_axis, result.collision_point);
        result.overlap = collision_result_help.smallest_overlap;
        return true;
    }

    /**
     * Checks if two polygons intersect using the Separating Axis Theorem (SAT).
     * @param polygon1 The first polygon to check for intersection.
     * @param polygon2 The second polygon to check for intersection.
     * @param axes1 The axes for the first polygon.
     * @param axes2 The axes for the second polygon.
     * @returns `true` if the two polygons intersect, `false` otherwise.
     */
    inline bool HasCollision(Polygon &polygon1, Polygon &polygon2, const std::vector<Axis> &axes1, const std::vector<Axis> &axes2) {
        return InnerLogic::AreProjectionsOverlapping(axes1, polygon1, polygon2) &&
            InnerLogic::AreProjectionsOverlapping(axes2, polygon1, polygon2);
    }
}