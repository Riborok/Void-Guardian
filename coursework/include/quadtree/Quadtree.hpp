#pragma once
#include "QuadtreeNode.hpp"
#include "../model/rectangle/RectangleData.hpp"

template <typename T, typename = std::enable_if_t<RequiresIdentifiableWithGetPolygon<T>::VALUE>>
class Quadtree final {
public:
    using Collision = typename QuadtreeNode<T>::Collision;
    using CollisionSet = typename QuadtreeNode<T>::CollisionSet;
private:
    QuadtreeNode<T> _root;
public:
    explicit Quadtree(const AlignedRectangleData &data, const size_t capacity);
    bool insert(T *element);
    bool remove(T *element);
    void fillCollisionSet(const Polygon &polygon, CollisionSet &collisions) const;
    [[nodiscard]] Collision getCollision(const Polygon &polygon, CollisionResult &collision_result) const;
    ~Quadtree() noexcept;

    Quadtree(Quadtree&&) noexcept = default;
    Quadtree& operator=(Quadtree&&) noexcept = delete;
    Quadtree(const Quadtree&) noexcept = delete;
    Quadtree& operator=(const Quadtree&) noexcept = delete;
};

#include "../../src/quadtree/Quadtree.hpp"