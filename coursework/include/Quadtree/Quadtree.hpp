#pragma once
#include "QuadtreeNode.hpp"

template <typename T, typename = std::enable_if_t<RequiresIdentifiableWithGetPolygon<T>::VALUE>>
class Quadtree final {
    QuadtreeNode<T> _root;

public:
    Quadtree(const float x_start, const float y_start, const float x_last, const float y_last);
    bool insert(T *element);
    bool remove(T *element);
    void getCollisions(Polygon &polygon, std::unordered_set<T*, IdentifiableHash> &collisions);
    ~Quadtree() noexcept;
    
    Quadtree(const Quadtree&) noexcept = delete;
    Quadtree& operator=(const Quadtree&) noexcept = delete;
    Quadtree(Quadtree&&) noexcept = delete;
    Quadtree& operator=(Quadtree&&) noexcept = delete;
};

#include "../../src/Quadtree/Quadtree.hpp"