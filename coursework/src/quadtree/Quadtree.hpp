#pragma once
#include "../../include/quadtree/Quadtree.hpp"

template <typename T, typename Enabler>
Quadtree<T, Enabler>::Quadtree(const AlignedRectangleData &data, const size_t capacity)
    : _root(data, capacity) {
}

template <typename T, typename Enabler>
bool Quadtree<T, Enabler>::insert(const T *element) {
    const Polygon &polygon = element->getPolygon();
    Axes axes;
    CollisionDetection::fillAxes(polygon, axes);
    if (_root.insert(element, axes))
        return true;
    delete element;
    return false;
}

template <typename T, typename Enabler>
bool Quadtree<T, Enabler>::remove(const T *element) {
    const Polygon &polygon = element->getPolygon();
    Axes axes;
    CollisionDetection::fillAxes(polygon, axes);
    return _root.remove(element, axes);
}

template <typename T, typename Enabler>
void Quadtree<T, Enabler>::fillCollisionSet(const Polygon &polygon, CollisionSet &collisions) const {
    Axes axes;
    CollisionDetection::fillAxes(polygon, axes);
    _root.fillCollisionSet(polygon, axes, collisions);
}

template <typename T, typename Enabler>
typename Quadtree<T, Enabler>::Collision Quadtree<T, Enabler>::getCollision(const Polygon& polygon) const {
    Axes axes;
    CollisionDetection::fillAxes(polygon, axes);
    return _root.getCollision(polygon, axes);
}

template <typename T, typename Enabler>
Quadtree<T, Enabler>::~Quadtree() noexcept {
    _root.destroyElements();
}
