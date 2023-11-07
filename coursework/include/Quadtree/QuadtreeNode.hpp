#pragma once

#include <unordered_set>
#include "QTAuxiliaryTools.hpp"

#include "../game/identifiable/Identifiable.hpp"
#include "../../include/geometry/collision/CollisionDetection.hpp"

template <typename T, typename = std::enable_if_t<RequiresIdentifiableWithGetPolygon<T>::VALUE>>
class QuadtreeNode final {
    static constexpr size_t CAPACITY = 12;
    static constexpr size_t HALF_CAPACITY = CAPACITY / 2;
    static constexpr size_t CHILD_COUNT = 4;

    size_t _total_elements = 0;
    std::unordered_set<T*, IdentifiableHash> _elements;
    QuadtreeNode *_children = nullptr;

    Boundary _boundary;

    [[nodiscard]] bool isSubdivide() const;

    void subdivide();
    void redistribute();
    void mergeWithChildren();

public:
    explicit QuadtreeNode(const float x_start, const float y_start, const float x_last, const float y_last);

    bool insert(T *element, const std::vector<Axis> &axes);
    bool remove(T *element, const std::vector<Axis> &axes);
    void getCollisions(Polygon &polygon, const std::vector<Axis> &axes,
        std::unordered_set<T*, IdentifiableHash> &collisions_info);
    void destroy();

    ~QuadtreeNode() noexcept;
    QuadtreeNode(QuadtreeNode&&) noexcept = default;
    QuadtreeNode& operator=(QuadtreeNode&&) noexcept = default;

    QuadtreeNode(const QuadtreeNode&) noexcept = delete;
    QuadtreeNode& operator=(const QuadtreeNode&) noexcept = delete;
};

#include "../../src/Quadtree/QuadtreeNode.hpp"