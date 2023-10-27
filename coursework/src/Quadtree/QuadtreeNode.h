#pragma once

#include <unordered_set>

#include "QTAuxiliaryTools.h"
#include "../geometry/collision/CollisionDetection.h"
#include "../game/identifiable/Identifiable.h"

#define CAPACITY 8 // NOLINT(modernize-macro-to-enum)
#define HALF_CAPACITY (CAPACITY / 2) // NOLINT(modernize-macro-to-enum)
#define CHILD_COUNT 4 // NOLINT(modernize-macro-to-enum)

template <typename T, typename = EnableIfIdPolygon<T>>
class QuadtreeNode final {
    size_t _total_polygons = 0;
    std::unordered_set<T*, IdentifiableHash> *_polygons = new std::unordered_set<T*, IdentifiableHash>;
    QuadtreeNode<T>* *_children = nullptr;

    Boundary _boundary;

    bool isSubdivide() const {
        return _polygons == nullptr;
    }

    void subdivide() {
        const sf::Vector2f *points = _boundary.points();
        
        const float x_start = points[0].x;
        const float y_start = points[0].y;
        const float x_last = points[2].x;
        const float y_last = points[2].y;

        const float width = (x_last - x_start) / 2;
        const float height = (y_last - y_start) / 2;
        
        _children = new QuadtreeNode<T>*[CHILD_COUNT];
        _children[0] = new QuadtreeNode<T>{ x_start, y_start, x_start + width, y_start + height };
        _children[1] = new QuadtreeNode<T>{ x_start + width, y_start, x_last, y_start + height };
        _children[2] = new QuadtreeNode<T>{ x_start, y_start + height, x_start + width, y_last };
        _children[3] = new QuadtreeNode<T>{ x_start + width, y_start + height, x_last, y_last };

        redistribute();
    }

    void redistribute() {
        _total_polygons = 0;

        for (auto *polygon : *_polygons) {
            std::vector<Axis> axes;
            CollisionDetection::getAxes(*polygon, axes);
        
            for (int i = 0; i < CHILD_COUNT; ++i) {
                _children[i]->insert(*polygon, axes);
            }
        }

        for (int i = 0; i < CHILD_COUNT; ++i) {
            _total_polygons += _children[i]->_total_polygons;
        }
        
        delete _polygons;
        _polygons = nullptr;
    }

    void mergeWithChildren() {
        _polygons = new std::unordered_set<T*, IdentifiableHash>;
        for (int i = 0; i < CHILD_COUNT; ++i) {
            if (_children[i]->isSubdivide())
                _children[i]->mergeWithChildren();
            
            for (auto *polygon : *(_children[i]->_polygons))
                _polygons->insert(polygon);

            delete _children[i];
        }
        delete []_children;
        _total_polygons = _polygons->size();
    }
public:
    explicit QuadtreeNode(const float x_start, const float y_start, const float x_last, const float y_last)
        : _boundary(x_start, y_start, x_last, y_last) { }

    void insert(T &t, const std::vector<Axis> &axes) {
        if (CollisionDetection::hasCollision(_boundary, t, _boundary.getAxes(), axes)) {
            if (isSubdivide()) {
                _total_polygons = 0;
                for (int i = 0; i < CHILD_COUNT; ++i) {
                    _children[i]->insert(t, axes);
                    _total_polygons += _children[i]->_total_polygons;
                }
            }
            else {
                _total_polygons++;
                _polygons->insert(&t);
                if (_polygons->size() > CAPACITY) {
                    subdivide();
                }
            }
        }
    }

    void remove(T &t, const std::vector<Axis> &axes) {
        if (CollisionDetection::hasCollision(_boundary, t, _boundary.getAxes(), axes)) {
            if (isSubdivide()) {
                _total_polygons = 0;
                for (int i = 0; i < CHILD_COUNT; ++i) {
                    _children[i]->remove(t, axes);
                    _total_polygons += _children[i]->_total_polygons;
                }
                if (_total_polygons <= HALF_CAPACITY) {
                    mergeWithChildren();
                }
            }
            else {
                _total_polygons--;
                _polygons->erase(&t);
            }
        }
    }

    void getCollisions(Polygon &polygon, const std::vector<Axis> &axes, std::unordered_set<T*, IdentifiableHash> &collisions_info) {
        if (isSubdivide()) {
            for (int i = 0; i < CHILD_COUNT; ++i) {
                if (CollisionDetection::hasCollision(_boundary, polygon, _boundary.getAxes(), axes)) {
                    _children[i]->getCollisions(polygon, axes, collisions_info);
                }
            }
        }
        else {
            for (auto *other_polygon : *_polygons) {
                std::vector<Axis> other_axes;
                CollisionDetection::getAxes(*other_polygon, other_axes);
                if (CollisionDetection::hasCollision(polygon, *other_polygon, axes, other_axes)) {
                    collisions_info.insert(other_polygon);
                }
            }
        }
    }

    ~QuadtreeNode() noexcept {
        if (isSubdivide()) {
            for (int i = 0; i < CHILD_COUNT; ++i)
                delete _children[i];
            delete []_children;
        }
        else
            delete _polygons;
    }
    
    QuadtreeNode(const QuadtreeNode&) noexcept = delete;
    QuadtreeNode& operator=(const QuadtreeNode&) noexcept = delete;
    QuadtreeNode(QuadtreeNode&&) noexcept = delete;
    QuadtreeNode& operator=(QuadtreeNode&&) noexcept = delete;
};