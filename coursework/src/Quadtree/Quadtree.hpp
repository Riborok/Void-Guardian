#pragma once
#include "../../include/Quadtree/Quadtree.hpp"

template <typename T, typename Enabler>
Quadtree<T, Enabler>::Quadtree(const AlignedRectangleData &data, const size_t capacity)
    : _root(data, capacity) {
}

template <typename T, typename Enabler>
bool Quadtree<T, Enabler>::insert(const T *element) {
    const Polygon &polygon = element->getPolygon();
    Axes axes;
    axes.reserve(polygon.getPoints().size());
    CollisionDetection::getAxes(polygon, axes);
    if (_root.insert(element, axes))
        return true;
    delete element;
    return false;
}

template <typename T, typename Enabler>
bool Quadtree<T, Enabler>::remove(const T *element) {
    const Polygon &polygon = element->getPolygon();
    Axes axes;
    axes.reserve(polygon.getPoints().size());
    CollisionDetection::getAxes(polygon, axes);
    return _root.remove(element, axes);
}

template <typename T, typename Enabler>
void Quadtree<T, Enabler>::getCollisions(const Polygon &polygon, CollisionSet &collisions) const {
    Axes axes;
    axes.reserve(polygon.getPoints().size());
    CollisionDetection::getAxes(polygon, axes);
    _root.getCollisions(polygon, axes, collisions);
}

template <typename T, typename Enabler>
Quadtree<T, Enabler>::~Quadtree() noexcept {
    _root.destroyElements();
}
