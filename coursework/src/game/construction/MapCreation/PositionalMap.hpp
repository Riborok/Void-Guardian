#pragma once
#include "../../../../include/game/construction/MapCreation/PositionalMap.hpp"

template <typename T>
size_t PositionalMap<T>::getIndex(const sf::Vector2i &position) const {
    return position.y * (_last_index.x + 1) + position.x;
}

template <typename T>
size_t PositionalMap<T>::getTotalCount() const {
    return static_cast<size_t>((_last_index.x + 1)) * (_last_index.y + 1);
}

template <typename T>
PositionalMap<T>::PositionalMap(const sf::Vector2i &last_index)  noexcept :
        _last_index(last_index),
        _array_2d(getTotalCount(), nullptr){
    _item_sequence.reserve(getTotalCount());
}

template <typename T>
bool PositionalMap<T>::set(T* location_info, const sf::Vector2i &position) {
    if (const auto index = getIndex(position); !_array_2d[index]) {
        _array_2d[index] = location_info;
        _item_sequence.push_back(location_info);
        return true;
    }
    return false;
}

template <typename T>
T* PositionalMap<T>::get(const sf::Vector2i &position) const {
    return _array_2d[getIndex(position)];
}

template <typename T>
const typename PositionalMap<T>::PtrArray &PositionalMap<T>::getItemSequence() const { return _item_sequence; }
    
template <typename T>
const sf::Vector2i &PositionalMap<T>::getLastIndex() const { return _last_index; }