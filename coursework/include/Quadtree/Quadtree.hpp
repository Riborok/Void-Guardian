#pragma once
#include "QuadtreeNode.hpp"

template <typename T, typename = std::enable_if_t<RequiresIdentifiableWithGetPolygon<T>::VALUE>>
class Quadtree final {
    QuadtreeNode<T> _root;
public:
    using CollisionSet = typename QuadtreeNode<T>::CollisionSet;
    
    Quadtree(const float x_start, const float y_start, const float x_last, const float y_last);
    bool insert(const T *element);
    bool remove(const T *element);
    void getCollisions(const Polygon &polygon, CollisionSet &collisions);
    ~Quadtree() noexcept;

    Quadtree(Quadtree&&) noexcept = default;
    Quadtree& operator=(Quadtree&&) noexcept = default;
    Quadtree(const Quadtree&) noexcept = delete;
    Quadtree& operator=(const Quadtree&) noexcept = delete;
};

#include "../../src/Quadtree/Quadtree.hpp"