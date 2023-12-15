#pragma once
#include <vector>
#include <SFML/System/Vector2.hpp>

template <typename T>
class PositionalMap final {
    typedef std::vector<T*> PtrArray;
    
    sf::Vector2i _last_index;
    PtrArray _array_2d;
    PtrArray _item_sequence;
    
    [[nodiscard]] size_t getIndex(const sf::Vector2i &position) const;
    [[nodiscard]] size_t getTotalCount() const;
public:
    explicit PositionalMap(const sf::Vector2i &last_index) noexcept;
    
    bool set(T* location_info, const sf::Vector2i &position);
    [[nodiscard]] T* get(const sf::Vector2i &position) const;
    
    [[nodiscard]] const PtrArray &getItemSequence() const;
    [[nodiscard]] const sf::Vector2i &getLastIndex() const;
    
    ~PositionalMap() noexcept = default;
    PositionalMap(PositionalMap&&) noexcept = delete;
    PositionalMap& operator=(PositionalMap&&) noexcept = delete;
    PositionalMap(const PositionalMap&) noexcept = delete;
    PositionalMap& operator=(const PositionalMap&) noexcept = delete;
};

#include "../../../../src/game/construction/game field creation/PositionalMap.hpp"