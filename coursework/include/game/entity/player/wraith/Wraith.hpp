#pragma once

#include "WraithStats.hpp"
#include "../../../../element/ReplaceableElement.hpp"

class Wraith final {
    friend class Player;
    
    ReplaceableElement* _element;
    WraithStats _wraith_stats;
    int _num;
public:
    Wraith(ReplaceableElement &element, const WraithStats &wraith_stats, const int num);
    [[nodiscard]] const Element& getElement() const;
    void setSpriteIndex(const size_t sprite_index) const;
    [[nodiscard]] const WraithStats& getStats() const;
    [[nodiscard]] int getNum() const;
    
    ~Wraith() noexcept = default;
    Wraith(Wraith&&) noexcept = default;
    Wraith& operator=(Wraith&&) noexcept = default;
    Wraith(const Wraith&) noexcept = delete;
    Wraith& operator=(const Wraith&) noexcept = delete;
};
