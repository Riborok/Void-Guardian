#pragma once
#include "QuadtreeNode.h"

template <typename T, typename = EnableIfIdPolygon<T>>
class Quadtree {
    QuadtreeNode<T> _root;
public:
    Quadtree(const float x_start, const float y_start, const float x_last, const float y_last)
        : _root(x_start, y_start, x_last, y_last) {
    }
    void Insert(T &t) {
        std::vector<Axis> axes;
        CollisionDetection::GetAxes(t, axes);
        _root.Insert(t, axes);
    }
    void GetCollisions(Polygon &polygon, std::unordered_set<T*, IdentifiableHash> &collisions) {
        std::vector<Axis> axes;
        CollisionDetection::GetAxes(polygon, axes);
        _root.GetCollisions(polygon, axes, collisions);
    }
    void Remove(T &t) {
        std::vector<Axis> axes;
        CollisionDetection::GetAxes(t, axes);
        _root.Remove(t, axes);
    }

    ~Quadtree() noexcept = default;
    Quadtree(const Quadtree&) noexcept = default;
    Quadtree& operator=(const Quadtree&) noexcept = default;
    Quadtree(Quadtree&&) noexcept = default;
    Quadtree& operator=(Quadtree&&) noexcept = default;
};
