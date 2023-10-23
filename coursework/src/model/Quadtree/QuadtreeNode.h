#pragma once

#include <unordered_set>

#include "QTAuxiliaryTools.h"
#include "../../game/identifiable/Identifiable.h"
#include "../../geometry/collision/CollisionDetection.h"

#define CAPACITY 8 // NOLINT(modernize-macro-to-enum)
#define HALF_CAPACITY (CAPACITY / 2) // NOLINT(modernize-macro-to-enum)
#define CHILD_COUNT 4 // NOLINT(modernize-macro-to-enum)

template <typename T, typename = EnableIfIdPolygon<T>>
class QuadtreeNode final {
    size_t _total_polygons = 0;
    std::unordered_set<T*, Identifiable> *_polygons = new std::unordered_set<T*, IdentifiableHash>;
    QuadtreeNode<T>* _children[CHILD_COUNT] = { };

    Boundary _boundary;

    bool IsSubdivide() const {
        return _polygons == nullptr;
    }

    void Subdivide() {
        const sf::Vector2f *points = _boundary.Points();
        
        const float x_start = points[0].x;
        const float y_start = points[0].y;
        const float x_last = points[2].x;
        const float y_last = points[2].y;

        const float width = (x_last - x_start) / 2;
        const float height = (y_last - y_start) / 2;
        
        _children[0] = new QuadtreeNode<T>{ x_start, y_start, x_start + width, y_start + height };
        _children[1] = new QuadtreeNode<T>{ x_start + width, y_start, x_last, y_start + height };
        _children[2] = new QuadtreeNode<T>{ x_start, y_start + height, x_start + width, y_last };
        _children[3] = new QuadtreeNode<T>{ x_start + width, y_start + height, x_last, y_last };

        Redistribute();
    }

    void Redistribute() {
        _total_polygons = 0;

        for (auto *polygon : *_polygons) {
            std::vector<Axis> axes;
            CollisionDetection::GetAxes(*polygon, axes);
            for (auto *child : _children) {
                child->Insert(*polygon, axes);
            }
        }

        for (auto *child : _children) {
            _total_polygons += child->_total_polygons;
        }
        
        delete _polygons;
        _polygons = nullptr;
    }

    void MergeWithChildren() {
        _polygons = new std::unordered_set<T*, IdentifiableHash>;
        for (auto *child : _children) {
            if (child->IsSubdivide())
                child->MergeWithChildren();
            
            for (auto *polygon : *(child->_polygons))
                _polygons->insert(polygon);

            delete child;
        }
        _total_polygons = _polygons->size();
    }
public:
    explicit QuadtreeNode(const float x_start, const float y_start, const float x_last, const float y_last)
        : _boundary(x_start, y_start, x_last, y_last) { }

    void Insert(T &t, const std::vector<Axis> &axes) {
        if (CollisionDetection::HasCollision(_boundary, t, _boundary.GetAxes(), axes)) {
            if (IsSubdivide()) {
                _total_polygons = 0;
                for (auto *child : _children) {
                    child->Insert(t, axes);
                    _total_polygons += child->_total_polygons;
                }
            }
            else {
                _total_polygons++;
                _polygons->insert(&t);
                if (_polygons->size() > CAPACITY) {
                    Subdivide();
                }
            }
        }
    }

    void Remove(T &t, const std::vector<Axis> &axes) {
        if (CollisionDetection::HasCollision(_boundary, t, _boundary.GetAxes(), axes)) {
            if (IsSubdivide()) {
                _total_polygons = 0;
                for (auto *child : _children) {
                    child->Remove(t, axes);
                    _total_polygons += child->_total_polygons;
                }
                if (_total_polygons <= HALF_CAPACITY) {
                    MergeWithChildren();
                }
            }
            else {
                _total_polygons--;
                _polygons->erase(&t);
            }
        }
    }

    void GetCollisions(Polygon &polygon, const std::vector<Axis> &axes, std::unordered_set<T*, IdentifiableHash> &collisions_info) {
        if (IsSubdivide()) {
            for (auto *child : _children) {
                if (CollisionDetection::HasCollision(_boundary, polygon, _boundary.GetAxes(), axes)) {
                    child->GetCollisions(polygon, axes, collisions_info);
                }
            }
        }
        else {
            for (auto *other_polygon : *_polygons) {
                std::vector<Axis> other_axes;
                CollisionDetection::GetAxes(*other_polygon, other_axes);
                if (CollisionDetection::HasCollision(polygon, *other_polygon, axes, other_axes)) {
                    collisions_info.insert(other_polygon);
                }
            }
        }
    }

    ~QuadtreeNode() noexcept {
        if (IsSubdivide())
            for (auto *child : _children)
                delete child;
        else
            delete _polygons;
    }
    
    QuadtreeNode(const QuadtreeNode&) noexcept = delete;
    QuadtreeNode& operator=(const QuadtreeNode&) noexcept = delete;
    QuadtreeNode(QuadtreeNode&&) noexcept = delete;
    QuadtreeNode& operator=(QuadtreeNode&&) noexcept = delete;
};