#pragma once
#include "QuadtreeNode.h"

template <typename T, typename = EnableIfIdPolygon<T>>
class Quadtree {
    QuadtreeNode<T> _root;
public:
    Quadtree(const float x_start, const float y_start, const float x_last, const float y_last)
        : _root(x_start, y_start, x_last, y_last) {
    }
    void insert(T &t) {
        std::vector<Axis> axes;
        CollisionDetection::getAxes(t, axes);
        _root.insert(t, axes);
    }
    void getCollisions(Polygon &polygon, std::unordered_set<T*, IdentifiableHash> &collisions) {
        std::vector<Axis> axes;
        CollisionDetection::getAxes(polygon, axes);
        _root.getCollisions(polygon, axes, collisions);
    }
    void remove(T &t) {
        std::vector<Axis> axes;
        CollisionDetection::getAxes(t, axes);
        _root.remove(t, axes);
    }

    ~Quadtree() noexcept = default;
    Quadtree(const Quadtree&) noexcept = default;
    Quadtree& operator=(const Quadtree&) noexcept = default;
    Quadtree(Quadtree&&) noexcept = default;
    Quadtree& operator=(Quadtree&&) noexcept = default;
};
