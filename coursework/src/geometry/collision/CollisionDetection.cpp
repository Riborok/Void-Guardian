#include "../../../include/geometry/collision/CollisionDetection.hpp"

#include "../../../include/geometry/GeomAuxiliaryFunc.hpp"
#include "../../../include/geometry/collision/ColisAuxiliaryTools.hpp"

namespace InnerLogic {
    constexpr float EPSILON = 1.0f;
    struct CollisionResultHelper final {
        float smallest_overlap = FLT_MAX;
        const Axis *collision_axis = nullptr;
        bool is_polygon1_axis = false;
    };
    
    void getProjection(const Polygon &polygon, const sf::Vector2f &axis, Projection &result) {
        const std::vector<sf::Vector2f> &points = polygon.getPoints();

        float min = GeomAuxiliaryFunc::dotProduct(axis, points[0]);
        float max = min;

        for (auto &point : points) {
            if (const float dot_product_result = GeomAuxiliaryFunc::dotProduct(axis, point); dot_product_result < min) {
                min = dot_product_result;
            }
            else if (dot_product_result > max) {
                max = dot_product_result;
            }
        }

        result = { min, max };
    }

    void getExtendedProjection(const Polygon &polygon, const sf::Vector2f &axis, const bool calculate_mid_point,
                               ExtendedProjection &result) {
        const std::vector<sf::Vector2f> &points = polygon.getPoints();

        float min = GeomAuxiliaryFunc::dotProduct(axis, points[0]);
        float max = min;
        sf::Vector2f min_point(points[0]);
        sf::Vector2f max_point(points[0]);

        for (auto &point : points) {
            if (const float dot_product_result = GeomAuxiliaryFunc::dotProduct(axis, point); dot_product_result < min) {
                min = dot_product_result;
                min_point = point;
            }
            else if (dot_product_result > max) {
                max = dot_product_result;
                max_point = point;
            }
            else if (calculate_mid_point && std::abs(dot_product_result - min) < EPSILON) {
                min_point = GeomAuxiliaryFunc::calcMidpoint(min_point, point);
            }
            else if (calculate_mid_point && std::abs(dot_product_result - max) < EPSILON) {
                max_point = GeomAuxiliaryFunc::calcMidpoint(max_point, point);
            }
        }

        result = {{min, max}, min_point, max_point };
    }

    bool areProjectionsOverlapping(const std::vector<Axis> &axes, const Polygon &polygon1, const Polygon &polygon2) {
        for (const auto &axis : axes) {
            Projection projection1;
            getProjection(polygon1, axis, projection1);
            Projection projection2;
            getProjection(polygon2, axis, projection2);

            if (std::min(projection1.max - projection2.min, projection2.max - projection1.min) <= 0) {
                return false;
            }
        }
        return true;
    }

    bool isSmallestOverlapAxisFound(const std::vector<Axis> &axes, const bool is_axes1,
            const Polygon &polygon1, const Polygon &polygon2, CollisionResultHelper &collision_result_help) {
        for (const auto &axis : axes) {
            Projection projection1;
            getProjection(polygon1, axis, projection1);
            Projection projection2;
            getProjection(polygon2, axis, projection2);

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

    void findClosestVertex(const Polygon &polygon1, const Polygon &polygon2, const Axis &axis,
                           const bool is_polygon1_axis, sf::Vector2f &result) {
        Projection projection;
        ExtendedProjection extended_projection;

        if (is_polygon1_axis && !GeomAuxiliaryFunc::areOrthogonal(polygon1.getRotation(), polygon2.getRotation())) {
            getProjection(polygon1, axis, projection);
            getExtendedProjection(polygon2, axis, false, extended_projection);
        }
        else {
            getProjection(polygon2, axis, projection);
            getExtendedProjection(polygon1, axis, true, extended_projection);
        }

        result = extended_projection.max - projection.min < projection.max - extended_projection.min
            ? extended_projection.max_point
            : extended_projection.min_point;
    }
}

void CollisionDetection::getAxes(const Polygon &polygon, std::vector<Axis> &axes) {
    const std::vector<sf::Vector2f> &points = polygon.getPoints();
    const size_t last_index = points.size() - 1;

    for (size_t i = 0; i < last_index; ++i) {
        axes.emplace_back(points[i], points[i + 1]);
    }
    axes.emplace_back(points[last_index], points[0]);
}

bool CollisionDetection::getCollisionResult(const Polygon &polygon1, const Polygon &polygon2, CollisionResult &result) {
    std::vector<Axis> axes1; axes1.reserve(polygon1.getPoints().size());
    getAxes(polygon1, axes1);
    std::vector<Axis> axes2; axes2.reserve(polygon2.getPoints().size());
    getAxes(polygon2, axes2);

    InnerLogic::CollisionResultHelper collision_result_help;

    if (!isSmallestOverlapAxisFound(axes1, true, polygon1, polygon2, collision_result_help) ||
            !isSmallestOverlapAxisFound(axes2, false, polygon1, polygon2, collision_result_help))
                return false;

    InnerLogic::findClosestVertex(polygon1, polygon2, *collision_result_help.collision_axis,
        collision_result_help.is_polygon1_axis, result.collision_point);
    result.overlap = collision_result_help.smallest_overlap;
    return true;
}

bool CollisionDetection::hasCollision(const Polygon &polygon1, const Polygon &polygon2,
                                      const std::vector<Axis> &axes1, const std::vector<Axis> &axes2) {
    return InnerLogic::areProjectionsOverlapping(axes1, polygon1, polygon2) &&
        InnerLogic::areProjectionsOverlapping(axes2, polygon1, polygon2);
}
