#pragma once
#include <SFML/System/Vector2.hpp>

template <typename T>
class Array2D final {
    sf::Vector2i _last_index;
    size_t _total_count;
    T* _array;
    [[nodiscard]] size_t getIndex(const sf::Vector2i &position) const;
public:
    Array2D(const sf::Vector2i &last_index, const T default_value);
    
    void set(T t, const sf::Vector2i &position);
    [[nodiscard]] T get(const sf::Vector2i &position) const;
    
    [[nodiscard]] const sf::Vector2i &getLastIndex() const;
    [[nodiscard]] size_t getTotalCount() const;
    
    ~Array2D() noexcept;
    Array2D(Array2D&&) noexcept = delete;
    Array2D& operator=(Array2D&&) noexcept = delete;
    Array2D(const Array2D&) noexcept = delete;
    Array2D& operator=(const Array2D&) noexcept = delete;
};

#include "../../../src/additionally/2DArray/Array2D.hpp"
