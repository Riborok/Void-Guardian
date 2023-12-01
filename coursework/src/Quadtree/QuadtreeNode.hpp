#pragma once
#include "../../include/Quadtree/QuadtreeNode.hpp"

template <typename T, typename Enabler>
QuadtreeNode<T, Enabler>::QuadtreeNode(const AlignedRectangleData &data, const size_t capacity):
        _capacity(capacity), _boundary(data) {
    _elements->reserve(_capacity);
}

template <typename T, typename Enabler>
bool QuadtreeNode<T, Enabler>::isSubdivide() const { return _children; }

template <typename T, typename Enabler>
void QuadtreeNode<T, Enabler>::subdivide() {
    const auto &points = _boundary.getPoints();
        
    const float x_start = points[0].x;
    const float y_start = points[0].y;
    const float x_last = points[2].x;
    const float y_last = points[2].y;

    const float width = (x_last - x_start) / 2;
    const float height = (y_last - y_start) / 2;
        
    _children = new QuadtreeNode[CHILD_COUNT]{
        QuadtreeNode{{x_start, y_start, x_start + width, y_start + height}, _capacity},
        QuadtreeNode{{x_start + width, y_start, x_last, y_start + height}, _capacity},
        QuadtreeNode{{x_start, y_start + height, x_start + width, y_last}, _capacity},
        QuadtreeNode{{x_start + width, y_start + height, x_last, y_last}, _capacity}
    };
        
    redistribute();
}

template <typename T, typename Enabler>
void QuadtreeNode<T, Enabler>::redistribute() {
    _total_elements = 0;

    for (auto *element : *_elements) {
        const Polygon &polygon = element->getPolygon();
        Axes axes; axes.reserve(polygon.getPoints().size());
        CollisionDetection::getAxes(polygon, axes);
        
        for (size_t i = 0; i < CHILD_COUNT; ++i) {
            _children[i].insert(element, axes);
        }
    }
    delete _elements;
        
    for (size_t i = 0; i < CHILD_COUNT; ++i) {
        _total_elements += _children[i]._total_elements;
    }
}

template <typename T, typename Enabler>
void QuadtreeNode<T, Enabler>::mergeWithChildren() {
    _elements = new CollisionSet; _elements->reserve(_capacity);
    for (size_t i = 0; i < CHILD_COUNT; ++i) {
        if (_children[i].isSubdivide())
            _children[i].mergeWithChildren();
            
        for (auto *element : *_children[i]._elements)
            _elements->insert(element);
    }
        
    delete []_children;
    _children = nullptr;
        
    _total_elements = _elements->size();
}

template <typename T, typename Enabler>
bool QuadtreeNode<T, Enabler>::insert(const T *element, const Axes &axes) {
    if (CollisionDetection::hasCollision(_boundary, element->getPolygon(),
        _boundary.getAxes(), axes)) {
        if (isSubdivide()) {
            _total_elements = 0;
            bool result = false;
            for (size_t i = 0; i < CHILD_COUNT; ++i) {
                result |= _children[i].insert(element, axes);
                _total_elements += _children[i]._total_elements;
            }
            return result;
        }
        else {
            ++_total_elements;
            _elements->insert(element);
            if (_elements->size() >= _capacity) {
                subdivide();
            }
            return true;
        }
    }
    return false;
}

template <typename T, typename Enabler>
bool QuadtreeNode<T, Enabler>::remove(const T *element, const Axes &axes) {
    if (CollisionDetection::hasCollision(_boundary, element->getPolygon(),
        _boundary.getAxes(), axes)) {
            if (isSubdivide()) {
                _total_elements = 0;
                bool result = false;
                for (size_t i = 0; i < CHILD_COUNT; ++i) {
                    result |= _children[i].remove(element, axes);
                    _total_elements += _children[i]._total_elements;
                }
                if (_total_elements <= _capacity / 2) {
                    mergeWithChildren();
                }
                return result;
            }
            else {
                const bool result = _elements->erase(element);
                if (result)
                    --_total_elements;
                return result;
            }
        }
    return false;
}

template <typename T, typename Enabler>
void QuadtreeNode<T, Enabler>::getCollisions(const Polygon &polygon, const Axes &axes, CollisionSet &collisions_info) const {
    if (isSubdivide()) {
        for (size_t i = 0; i < CHILD_COUNT; ++i) {
            if (CollisionDetection::hasCollision(_boundary, polygon,
                _boundary.getAxes(), axes)) {
                _children[i].getCollisions(polygon, axes, collisions_info);
                }
        }
    }
    else {
        for (auto *other_element : *_elements) {
            if (collisions_info.find(other_element) == collisions_info.end()) {
                const Polygon &other_polygon = other_element->getPolygon();
                Axes other_axes; other_axes.reserve(other_polygon.getPoints().size());
                CollisionDetection::getAxes(other_polygon, other_axes);
                if (CollisionDetection::hasCollision(polygon, other_polygon,
                        axes, other_axes))
                            collisions_info.insert(other_element);
            }
        }
    }
}

template <typename T, typename Enabler>
void QuadtreeNode<T, Enabler>::destroyElements() {
    if (isSubdivide())
        mergeWithChildren();
    for (const auto *element : *_elements)
        delete element;
}

template <typename T, typename Enabler>
QuadtreeNode<T, Enabler>::~QuadtreeNode() noexcept {
    if (isSubdivide())
        delete []_children;
    else
        delete _elements;
}