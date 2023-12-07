#include <algorithm>
#include <cassert>
#include "../../../include/geometry/collision/CollisionTable.hpp"

CollisionTable::CollisionTable(const InitList &pairs) {
    assert(checkUniqueElementTypes(pairs)
        && "Error in CollisionTable constructor: Duplicate ElementType found");
    assert(pairs.size() <= COUNT
        && "Error in CollisionTable constructor: Size of pairs should be less than or equal to ELEMENT_TYPES_COUNT");
    
    std::fill(_table.begin(), _table.end(), nullptr);
    _cleanup_list.reserve(pairs.size());
    for (const auto& [element_type, set_element_types] : pairs) {
        assert(toSizeT(element_type) < COUNT && "Error in CollisionTable constructor: Index out of bounds");
        _table[toSizeT(element_type)] = set_element_types;
        _cleanup_list.push_back(set_element_types);
    }
}

const CollisionTable::AvailableCollisions* CollisionTable::operator[](const ElementType index) const {
    assert(toSizeT(index) < COUNT && "Error in CollisionTable operator[]: Index out of bounds");
    return _table[toSizeT(index)];
}

CollisionTable::~CollisionTable() noexcept {
    for (const auto *ptr : _cleanup_list)
        delete ptr;
}