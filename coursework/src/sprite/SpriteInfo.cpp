#include "../../include/sprite/SpriteInfo.hpp"
#include "../../include/additionally/AdditionalFunc.hpp"
#include <cassert>


SimpleSpriteInfos::SimpleSpriteInfos(const InitList &pairs) {
    assert(checkUniqueElementTypes(pairs)
        && "Error in SimpleSpriteInfos constructor: Duplicate ElementType found");
    assert(pairs.size() == COUNT
        && "Error in SimpleSpriteInfos constructor: Size of pairs should be strictly equal to "
           "ANIMATED_TYPES_START (the amount of non-animated sprite types)");
    
    for (const auto& [fst, snd] : pairs) {
        assert(toSizeT(fst) < COUNT && "Error in SimpleSpriteInfos constructor: Index out of bounds");
        _arr[toSizeT(fst)] = std::move(snd);
    }
}

const SimpleSpriteInfo& SimpleSpriteInfos::operator[](const ElementType index) const {
    assert(toSizeT(index) < COUNT && "Error in SimpleSpriteInfos operator[]: Index out of bounds");
    return _arr[toSizeT(index)];
}

AnimatedSpriteInfos::AnimatedSpriteInfos(const InitList &pairs) {
    assert(checkUniqueElementTypes(pairs)
        && "Error in AnimatedSpriteInfos constructor: Duplicate ElementType found");
    assert(pairs.size() == COUNT
        && "Error in AnimatedSpriteInfos constructor: Size of pairs should be strictly equal to "
           "ELEMENT_TYPES_COUNT - ANIMATED_TYPES_START (the amount of animated sprite types)");
    
    for (const auto& [fst, snd] : pairs) {
        assert(toSizeT(fst) >= START_INDEX && toSizeT(fst) - START_INDEX < COUNT
            && "Error in AnimatedSpriteInfos constructor: Index out of bounds");
        _arr[toSizeT(fst) - START_INDEX] = std::move(snd);
    }
}

const AnimatedSpriteInfo& AnimatedSpriteInfos::operator[](const ElementType index) const {
    assert(toSizeT(index) >= START_INDEX && toSizeT(index) - START_INDEX < COUNT
        && "Error in AnimatedSpriteInfos operator[]: Index out of bounds");
    return _arr[toSizeT(index) - START_INDEX];
}