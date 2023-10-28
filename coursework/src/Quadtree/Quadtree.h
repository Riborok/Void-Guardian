#pragma once
#include "QuadtreeNode.h"

class Quadtree final {
    QuadtreeNode _root;
public:
    Quadtree(const float x_start, const float y_start, const float x_last, const float y_last)
        : _root(x_start, y_start, x_last, y_last) {
    }
    void insert(Element &element) {
        std::vector<Axis> axes;
        CollisionDetection::getAxes(element.getEntity(), axes);
        _root.insert(element, axes);
    }
    void getCollisions(Polygon &polygon, std::unordered_set<Element*, IdentifiableHash> &collisions) {
        std::vector<Axis> axes;
        CollisionDetection::getAxes(polygon, axes);
        _root.getCollisions(polygon, axes, collisions);
    }
    void remove(Element &element) {
        std::vector<Axis> axes;
        CollisionDetection::getAxes(element.getEntity(), axes);
        _root.remove(element, axes);
    }

    ~Quadtree() noexcept = default;
    
    Quadtree(const Quadtree&) noexcept = delete;
    Quadtree& operator=(const Quadtree&) noexcept = delete;
    Quadtree(Quadtree&&) noexcept = delete;
    Quadtree& operator=(Quadtree&&) noexcept = delete;
};
