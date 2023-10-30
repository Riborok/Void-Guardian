#pragma once
#include "QuadtreeNode.h"

class Quadtree final {
    QuadtreeNode _root;
public:
    Quadtree(const float x_start, const float y_start, const float x_last, const float y_last)
        : _root(x_start, y_start, x_last, y_last) {
    }
    /**
     * Attempt to insert an element into the data structure.
     * @param element The element to insert.
     * @return True if the insertion was successful, false otherwise.
     *         If insertion fails, this method also frees the memory allocated for the element.
     */
    bool insert(Element *element) {
        std::vector<Axis> axes;
        CollisionDetection::getAxes(element->getEntity(), axes);
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
    bool remove(Element *element) {
        std::vector<Axis> axes;
        CollisionDetection::getAxes(element->getEntity(), axes);
        return _root.remove(element, axes);
    }
    /**
     * Find collisions between a given polygon and elements in the data structure.
     * @param polygon The polygon for which collisions are to be detected.
     * @param collisions A set to store pointers to elements that collide with the polygon.
     */
    void getCollisions(Polygon &polygon, std::unordered_set<Element*, IdentifiableHash> &collisions) {
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
