#include <algorithm>
#include <cassert>
#include "../../../include/geometry/collision/CollisionTable.hpp"
#include "../../../include/additionally/AdditionalFunc.hpp"

CollisionTable::CollisionTable(const std::initializer_list<std::pair<ElementType, const AvailableCollisions*>> &pairs) {
    assert(checkUniqueElementTypes(pairs)
        && "Error in CollisionTable constructor: Duplicate ElementType found");
    assert(pairs.size() <= COUNT
        && "Error in CollisionTable constructor: Size of pairs should be less than or equal to ELEMENT_TYPES_COUNT");
    
    std::fill(_table.begin(), _table.end(), nullptr);
    _cleanup_list.reserve(pairs.size());
    for (const auto& [fst, snd] : pairs) {
        assert(toSizeT(fst) < COUNT && "Error in CollisionTable constructor: Index out of bounds");
        _table[toSizeT(fst)] = snd;
        _cleanup_list.push_back(snd);
    }
}

const AvailableCollisions* CollisionTable::operator[](const ElementType index) const {
    assert(toSizeT(index) < COUNT && "Error in CollisionTable operator[]: Index out of bounds");
    return _table[toSizeT(index)];
}

CollisionTable::~CollisionTable() noexcept {
    for (const auto *ptr : _cleanup_list)
        delete ptr;
}