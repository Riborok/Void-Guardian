#pragma once
#include "QuadtreeNode.h"

template <typename T>
class Quadtree final {
    static_assert(RequiresIdentifiableWithGetPolygon<T>::VALUE, "Type T must derive from Identifiable and provide a getPolygon method");
    
    QuadtreeNode<T> _root;
public:
    Quadtree(const float x_start, const float y_start, const float x_last, const float y_last)
        : _root(x_start, y_start, x_last, y_last) {
    }
    /**
     * Attempt to insert an element into the data structure.
     * @param element The element to insert.
     * @return True if the insertion was successful, false otherwise.
     * @note If insertion fails, this method frees the memory allocated for the element.
     */
    bool insert(T *element) {
        std::vector<Axis> axes;
        CollisionDetection::getAxes(element->getPolygon(), axes);
        if (_root.insert(element, axes))
            return true;
        delete element;
        return false;
    }
    /**
     * Remove an element from the data structure.
     * @param element The element to remove.
     * @return True if the element was successfully removed, false otherwise.
     */
    bool remove(T *element) {
        std::vector<Axis> axes;
        CollisionDetection::getAxes(element->getPolygon(), axes);
        return _root.remove(element, axes);
    }
    /**
     * Find collisions between a given polygon and elements in the data structure.
     * @param polygon The polygon for which collisions are to be detected.
     * @param collisions A set to store pointers to elements that collide with the polygon.
     */
    void getCollisions(Polygon &polygon, std::unordered_set<T*, IdentifiableHash> &collisions) {
        std::vector<Axis> axes;
        CollisionDetection::getAxes(polygon, axes);
        _root.getCollisions(polygon, axes, collisions);
    }

    ~Quadtree() noexcept { _root.destroy(); }
    
    Quadtree(const Quadtree&) noexcept = delete;
    Quadtree& operator=(const Quadtree&) noexcept = delete;
    Quadtree(Quadtree&&) noexcept = delete;
    Quadtree& operator=(Quadtree&&) noexcept = delete;
};
