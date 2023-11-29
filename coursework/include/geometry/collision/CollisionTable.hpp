#pragma once

#include <array>
#include <vector>
#include <unordered_set>

#include "../../element/ElementType.hpp"

typedef std::unordered_set<ElementType, ElementTypesHash> AvailableCollisions;

class CollisionTable final {
    static constexpr size_t COUNT = ELEMENT_TYPES_COUNT;
    typedef std::initializer_list<std::pair<const ElementType, const AvailableCollisions*>> InitList;
    typedef std::array<const AvailableCollisions*, COUNT> AvailableCollisionsTable;
    typedef std::vector<const AvailableCollisions*> CleanupList;
    
    AvailableCollisionsTable _table;
    CleanupList _cleanup_list;
public:
    CollisionTable(const InitList &pairs);

    const AvailableCollisions* operator[](const ElementType index) const;

    ~CollisionTable() noexcept;
    CollisionTable(CollisionTable&&) noexcept = default;
    CollisionTable& operator=(CollisionTable&&) noexcept = default;
    CollisionTable(const CollisionTable&) noexcept = delete;
    CollisionTable& operator=(const CollisionTable&) noexcept = delete;
};