#pragma once
#include "QuadtreeNode.hpp"
#include "../model/polygon/RectangleData.hpp"

template <typename T, typename = std::enable_if_t<RequiresIdentifiableWithGetPolygon<T>::VALUE>>
class Quadtree final {
public:
    using CollisionSet = typename QuadtreeNode<T>::CollisionSet;
private:
    QuadtreeNode<T> _root;
public:
    explicit Quadtree(const AlignedRectangleData &data, const size_t capacity);
    bool insert(const T *element);
    bool remove(const T *element);
    void getCollisions(const Polygon &polygon, CollisionSet &collisions) const;
    ~Quadtree() noexcept;

    Quadtree(Quadtree&&) noexcept = default;
    Quadtree& operator=(Quadtree&&) noexcept = default;
    Quadtree(const Quadtree&) noexcept = delete;
    Quadtree& operator=(const Quadtree&) noexcept = delete;
};

#include "../../src/quadtree/Quadtree.hpp"