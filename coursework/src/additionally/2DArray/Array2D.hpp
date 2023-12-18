#pragma once
#include <algorithm>
#include "../../../include/additionally/2DArray/Array2D.hpp"

template <typename T>
size_t Array2D<T>::getIndex(const sf::Vector2i &position) const {
    return position.y * (_last_index.x + 1) + position.x;
}

template <typename T>
Array2D<T>::Array2D(const sf::Vector2i& last_index, const T default_value):
        _last_index(last_index), _total_count(static_cast<size_t>((_last_index.x + 1)) * (_last_index.y + 1)),
        _array(new T[_total_count]) {
    std::fill(_array, _array + _total_count, default_value);
}

template <typename T>
void Array2D<T>::set(T t, const sf::Vector2i& position) { _array[getIndex(position)] = t; }

template <typename T>
T Array2D<T>::get(const sf::Vector2i& position) const { return _array[getIndex(position)]; }

template <typename T>
const sf::Vector2i &Array2D<T>::getLastIndex() const { return _last_index; }

template <typename T>
size_t Array2D<T>::getTotalCount() const { return _total_count; }

template <typename T>
Array2D<T>::~Array2D() noexcept { delete[] _array; }