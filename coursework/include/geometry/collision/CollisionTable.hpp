#pragma once
#include <array>
#include <vector>
#include <unordered_set>

#include "../../element/ElementType.hpp"
#include "../../additionally/Initialization.hpp"

class CollisionTable final {
public:
    typedef std::unordered_set<ElementType, ElementTypesHash> AvailableCollisions;
private:
    static constexpr size_t COUNT = ELEMENT_TYPES_COUNT;
    typedef std::array<const AvailableCollisions*, COUNT> AvailableCollisionsTable;
    using InitList = InitializerList<AvailableCollisions*>;

    AvailableCollisions _ray_collisions;
    AvailableCollisionsTable _table;
public:
    CollisionTable(AvailableCollisions &&ray_collisions, const InitList &init_list);

    [[nodiscard]] const AvailableCollisions* operator[](const ElementType index) const;
    [[nodiscard]] const AvailableCollisions& getRayCollisions() const;

    ~CollisionTable() noexcept;
    CollisionTable(CollisionTable&& collision_table) noexcept;
    CollisionTable& operator=(CollisionTable&&) noexcept = delete;
    CollisionTable(const CollisionTable& collision_table) noexcept;
    CollisionTable& operator=(const CollisionTable&) noexcept = delete;
};