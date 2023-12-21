// ReSharper disable CppNoDiscardExpression
#pragma once
#include "../../include/sprite/Infos.hpp"
#include "../../include/additionally/RandomGenerator.hpp"
#include <cassert>

template <size_t StartIndex, size_t Count, typename Abstract, typename Info, typename T0, typename T1>
const typename SpriteInfos<StartIndex, Count, Abstract, Info, T0, T1>::InfoVector&
SpriteInfos<StartIndex, Count, Abstract, Info, T0, T1>::addInfoFromAbstract(const size_t index, const size_t num) {
    InfoVector result;
    
    const auto& abstract_infos = _abstract_infos[index];
    result.reserve(abstract_infos.size());
    for (const auto& info : abstract_infos)
        result.emplace_back(info, num);

    return _infos[index].emplace(num, std::move(result)).first->second;
}

template <size_t StartIndex, size_t Count, typename Abstract, typename Info, typename T0, typename T1>
void SpriteInfos<StartIndex, Count, Abstract, Info, T0, T1>::handleTextureLoad(const size_t index,
        const sf::Vector2i& texture_load_range) {
    for (auto i = texture_load_range.x; i < texture_load_range.y; ++i)
        addInfoFromAbstract(index, i);
}

template <size_t StartIndex, size_t Count, typename Abstract, typename Info, typename T0, typename T1>
SpriteInfos<StartIndex, Count, Abstract, Info, T0, T1>::SpriteInfos(const InitList& init_list) {
    assert(checkUniqueElementTypes(init_list)
        && "Error in SpriteInfos constructor: Duplicate ElementType found");
    assert(init_list.size() == Count
        && "Error in SpriteInfos constructor: List size should be strictly equal to Count");
    
    for (const auto& [element_type, initializer_info] : init_list) {
        const size_t index = toSizeT(element_type) - StartIndex;
        assert(toSizeT(element_type) >= StartIndex && index < Count
            && "Error in SpriteInfos constructor: Index out of bounds");
        _abstract_infos[index] = std::move(initializer_info.info);
        handleTextureLoad(index, initializer_info.texture_load_range);
    }
}

template <size_t StartIndex, size_t Count, typename Abstract, typename Info, typename T0, typename T1>
const typename SpriteInfos<StartIndex, Count, Abstract, Info, T0, T1>::InfoVector&
SpriteInfos<StartIndex, Count, Abstract, Info, T0, T1>::getInfo(const ElementType element_type, const size_t num) {
    const size_t index = toSizeT(element_type) - StartIndex;
    assert(toSizeT(element_type) >= StartIndex && index < Count
        && "Error in SpriteInfos getInfo: Index out of bounds");

    const auto& map = _infos[index];
    if (const auto it = map.find(num); it != map.end()) 
        return it->second;
    
    return addInfoFromAbstract(index, num);
}

template <size_t StartIndex, size_t Count, typename Abstract, typename Info, typename T0, typename T1>
void SpriteInfos<StartIndex, Count, Abstract, Info, T0, T1>::addInfoFromAbstract(const ElementType element_type,
        const size_t num) {
    const size_t index = toSizeT(element_type) - StartIndex;
    assert(toSizeT(element_type) >= StartIndex && index < Count
        && "Error in SpriteInfos getInfo: Index out of bounds");
    
    addInfoFromAbstract(index, num);
}