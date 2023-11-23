#pragma once

#include <unordered_set>
#include "QTAuxiliaryTools.hpp"

#include "../game/identifiable/Identifiable.hpp"
#include "../../include/geometry/collision/CollisionDetection.hpp"

template <typename T, typename = std::enable_if_t<RequiresIdentifiableWithGetPolygon<T>::VALUE>>
class QuadtreeNode final {
public:
    using CollisionSet = std::unordered_set<const T*, IdentifiableHash>;
private:
    static constexpr size_t CAPACITY = 12;
    static constexpr size_t HALF_CAPACITY = CAPACITY / 2;
    static constexpr size_t CHILD_COUNT = 4;

    size_t _total_elements = 0;
    CollisionSet _elements;
    QuadtreeNode *_children = nullptr;

    Boundary _boundary;

    [[nodiscard]] bool isSubdivide() const;

    void subdivide();
    void redistribute();
    void mergeWithChildren();
public:
    explicit QuadtreeNode(const AlignedRectangleData &data);

    bool insert(const T *element, const std::vector<Axis> &axes);
    bool remove(const T *element, const std::vector<Axis> &axes);
    void getCollisions(const Polygon &polygon, const std::vector<Axis> &axes, CollisionSet &collisions_info) const;
    void destroy();

    ~QuadtreeNode() noexcept;
    QuadtreeNode(QuadtreeNode&&) noexcept = default;
    QuadtreeNode& operator=(QuadtreeNode&&) noexcept = default;

    QuadtreeNode(const QuadtreeNode&) noexcept = delete;
    QuadtreeNode& operator=(const QuadtreeNode&) noexcept = delete;
};

#include "../../src/Quadtree/QuadtreeNode.hpp"