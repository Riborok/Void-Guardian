#pragma once
#include "../../../include/additionally/2DArray/SequentialArray2D.hpp"

template <typename T>
SequentialArray2D<T>::SequentialArray2D(const sf::Vector2i &last_index, const T default_value):
        _array_2d(last_index, default_value) {
    _item_sequence.reserve(_array_2d.getTotalCount());
}

template <typename T>
void SequentialArray2D<T>::set(T t, const sf::Vector2i& position) {
    _array_2d.set(t, position);
    _item_sequence.push_back(t);
}

template <typename T>
const typename SequentialArray2D<T>::Sequence& SequentialArray2D<T>::getItemSequence() const { return _item_sequence; }

template <typename T>
const Array2D<T>& SequentialArray2D<T>::getArray2D() const { return _array_2d; }