#pragma once
#include <vector>

#include "Array2D.hpp"

template <typename T>
class SequentialArray2D final {
public:
    typedef std::vector<T> Sequence;
private:
    Array2D<T> _array_2d;
    Sequence _item_sequence;
public:
    SequentialArray2D(const sf::Vector2i &last_index, const T default_value);
    void set(T t, const sf::Vector2i &position);
    [[nodiscard]] const Sequence& getItemSequence() const;
    [[nodiscard]] const Array2D<T>& getArray2D() const;
    
    ~SequentialArray2D() noexcept = default;
    SequentialArray2D(SequentialArray2D&&) noexcept = delete;
    SequentialArray2D& operator=(SequentialArray2D&&) noexcept = delete;
    SequentialArray2D(const SequentialArray2D&) noexcept = delete;
    SequentialArray2D& operator=(const SequentialArray2D&) noexcept = delete;
};

#include "../../../src/additionally/2DArray/SequentialArray2D.hpp"
