#pragma once

#include <unordered_set>
#include "QTAuxiliaryTools.hpp"

#include "../game/identifiable/Identifiable.hpp"
#include "../../include/geometry/collision/CollisionDetection.hpp"

template <typename T, typename = std::enable_if_t<RequiresIdentifiableWithGetPolygon<T>::VALUE>>
class QuadtreeNode final {
public:
    using Collision = T*;
    using CollisionSet = std::unordered_set<Collision, IdentifiableHash>;
private:
    static constexpr size_t CHILD_COUNT = 4;

    size_t _capacity;
    size_t _total_elements = 0;
    CollisionSet *_elements = new CollisionSet;
    QuadtreeNode *_children = nullptr;
    Boundary _boundary;

    [[nodiscard]] bool isSubdivide() const;

    void subdivide();
    void redistribute();
    void mergeWithChildren();
public:
    explicit QuadtreeNode(const AlignedRectangleInfo &aligned_rect_info, const size_t capacity);

    bool insert(T *element, const Axes &axes);
    bool remove(T *element, const Axes &axes);
    void fillCollisionSet(const Polygon &polygon, const Axes &axes, CollisionSet &collisions_info) const;
    [[nodiscard]] Collision getCollision(const Polygon &polygon, const Axes &axes, CollisionResult &collision_result) const;
    void destroyElements();

    ~QuadtreeNode() noexcept;
    QuadtreeNode(QuadtreeNode&& quadtree_node) noexcept;
    QuadtreeNode& operator=(QuadtreeNode&&) noexcept = delete;
    QuadtreeNode(const QuadtreeNode&) noexcept = delete;
    QuadtreeNode& operator=(const QuadtreeNode&) noexcept = delete;
};

#include "../../src/quadtree/QuadtreeNode.hpp"