#include <algorithm>
#include <cassert>
#include "../../../include/geometry/collision/CollisionTable.hpp"

CollisionTable::CollisionTable(AvailableCollisions &&ray_collisions, const InitList &init_list) {
    assert(checkUniqueElementTypes(init_list)
        && "Error in CollisionTable constructor: Duplicate ElementType found");
    assert(init_list.size() <= COUNT
        && "Error in CollisionTable constructor: List size should be less than or equal to ELEMENT_TYPES_COUNT");

    _ray_collisions = std::move(ray_collisions);
    
    std::fill(_table.begin(), _table.end(), nullptr);
    for (const auto& [element_type, set_element_types] : init_list) {
        assert(toSizeT(element_type) < COUNT && "Error in CollisionTable constructor: Index out of bounds");
        _table[toSizeT(element_type)] = set_element_types;
    }
}

const CollisionTable::AvailableCollisions* CollisionTable::operator[](const ElementType index) const {
    assert(toSizeT(index) < COUNT && "Error in CollisionTable operator[]: Index out of bounds");
    return _table[toSizeT(index)];
}

const CollisionTable::AvailableCollisions& CollisionTable::getRayCollisions() const { return _ray_collisions; }

CollisionTable::~CollisionTable() noexcept {  // NOLINT(modernize-use-equals-default)
    for (const auto *ptr : _table)
        delete ptr;
}

CollisionTable::CollisionTable(CollisionTable&& collision_table) noexcept:
        _ray_collisions(std::move(collision_table._ray_collisions)),
        _table(collision_table._table) {
    std::fill(collision_table._table.begin(), collision_table._table.end(), nullptr);
}

CollisionTable::CollisionTable(const CollisionTable& collision_table) noexcept {
    _ray_collisions = collision_table._ray_collisions;
    
    std::fill(_table.begin(), _table.end(), nullptr);
    for (size_t i = 0; i < collision_table._table.size(); ++i)
        if (const AvailableCollisions* available_collision = collision_table._table[i]; available_collision)
            _table[i] = new AvailableCollisions(*available_collision);
}
