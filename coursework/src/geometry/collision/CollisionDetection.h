#pragma once

#include <vector>

#include <cmath>
#include "ColisAuxiliaryTools.h"
#include "Axis.h"
#include "../GeomAuxiliaryFunc.h"
#include "../../model/polygon/Polygon.h"
#define EPSILON 1 // NOLINT(modernize-macro-to-enum)

namespace CollisionDetection {
    namespace InnerLogic {
        inline void GetProjection(Polygon &polygon, const sf::Vector2f &axis, Projection &result) {
            const sf::Vector2f *points = polygon.Points();
            const size_t amount = polygon.PointsAmount();
    
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
            const size_t amount = polygon.PointsAmount();

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
            for (const Axis& axis : axes) {
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