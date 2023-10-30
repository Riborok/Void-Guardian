#pragma once

#include <unordered_set>

#include "QTAuxiliaryTools.h"
#include "../element/Element.h"
#include "../geometry/collision/CollisionDetection.h"
#include "../game/identifiable/Identifiable.h"

class QuadtreeNode final {
    enum : std::size_t {
        CAPACITY = 8,
        HALF_CAPACITY = CAPACITY / 2,
    };
    enum : int { CHILD_COUNT = 4 };
    
    size_t _total_elements = 0;
    std::unordered_set<Element*, IdentifiableHash> _elements;
    QuadtreeNode *_children = nullptr;

    Boundary _boundary;

    bool isSubdivide() const { return _children; }

    void subdivide() {
        const sf::Vector2f *points = _boundary.points();
        
        const float x_start = points[0].x;
        const float y_start = points[0].y;
        const float x_last = points[2].x;
        const float y_last = points[2].y;

        const float width = (x_last - x_start) / 2;
        const float height = (y_last - y_start) / 2;
        
        _children = new QuadtreeNode[CHILD_COUNT]{
            QuadtreeNode{x_start, y_start, x_start + width, y_start + height},
            QuadtreeNode{x_start + width, y_start, x_last, y_start + height},
            QuadtreeNode{x_start, y_start + height, x_start + width, y_last},
            QuadtreeNode{x_start + width, y_start + height, x_last, y_last}
        };
        
        redistribute();
    }

    void redistribute() {
        _total_elements = 0;

        for (auto *element : _elements) {
            std::vector<Axis> axes;
            CollisionDetection::getAxes(element->getEntity(), axes);
        
            for (int i = 0; i < CHILD_COUNT; ++i) {
                _children[i].insert(*element, axes);
            }
        }
        _elements.clear();
        
        for (int i = 0; i < CHILD_COUNT; ++i) {
            _total_elements += _children[i]._total_elements;
        }
    }

    void mergeWithChildren() {
        for (int i = 0; i < CHILD_COUNT; ++i) {
            if (_children[i].isSubdivide())
                _children[i].mergeWithChildren();
            
            for (auto *element : _children[i]._elements)
                _elements.insert(element);
        }
        
        delete []_children;
        _children = nullptr;
        
        _total_elements = _elements.size();
    }
public:
    explicit QuadtreeNode(const float x_start, const float y_start, const float x_last, const float y_last)
        : _boundary(x_start, y_start, x_last, y_last) { }

    void insert(Element &element, const std::vector<Axis> &axes) {
        if (CollisionDetection::hasCollision(_boundary, element.getEntity(),
            _boundary.getAxes(), axes)) {
            if (isSubdivide()) {
                _total_elements = 0;
                for (int i = 0; i < CHILD_COUNT; ++i) {
                    _children[i].insert(element, axes);
                    _total_elements += _children[i]._total_elements;
                }
            }
            else {
                ++_total_elements;
                _elements.insert(&element);
                if (_elements.size() > CAPACITY) {
                    subdivide();
                }
            }
        }
    }

    void remove(Element &element, const std::vector<Axis> &axes) {
        if (CollisionDetection::hasCollision(_boundary, element.getEntity(),
            _boundary.getAxes(), axes)) {
            if (isSubdivide()) {
                _total_elements = 0;
                for (int i = 0; i < CHILD_COUNT; ++i) {
                    _children[i].remove(element, axes);
                    _total_elements += _children[i]._total_elements;
                }
                if (_total_elements <= HALF_CAPACITY) {
                    mergeWithChildren();
                }
            }
            else {
                _total_elements--;
                _elements.erase(&element);
            }
        }
    }

    void getCollisions(Polygon &polygon, const std::vector<Axis> &axes,
            std::unordered_set<Element*, IdentifiableHash> &collisions_info) {
        if (isSubdivide()) {
            for (int i = 0; i < CHILD_COUNT; ++i) {
                if (CollisionDetection::hasCollision(_boundary, polygon,
                    _boundary.getAxes(), axes)) {
                    _children[i].getCollisions(polygon, axes, collisions_info);
                }
            }
        }
        else {
            for (auto *other_element : _elements) {
                std::vector<Axis> other_axes;
                CollisionDetection::getAxes(other_element->getEntity(), other_axes);
                if (CollisionDetection::hasCollision(polygon, other_element->getEntity(),
                    axes, other_axes)) {
                    collisions_info.insert(other_element);
                }
            }
        }
    }

    ~QuadtreeNode() noexcept { delete []_children; }
    QuadtreeNode(QuadtreeNode&&) noexcept = default;
    QuadtreeNode& operator=(QuadtreeNode&&) noexcept = default;
        
    QuadtreeNode(const QuadtreeNode&) noexcept = delete;
    QuadtreeNode& operator=(const QuadtreeNode&) noexcept = delete;
};