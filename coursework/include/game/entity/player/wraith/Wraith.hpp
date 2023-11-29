#pragma once

#include "WraithStats.hpp"
#include "../../../../element/ReplaceableElement.hpp"

class Wraith final {
    ReplaceableElement* _element;
    WraithStats _wraith_stats;

    bool _is_mirrored = false;
    void mirrorHorizontally();
public:
    Wraith(ReplaceableElement &element, const WraithStats &wraith_stats);
    [[nodiscard]] const Element& getElement() const;
    void setSpriteIndex(const size_t sprite_index) const;
    [[nodiscard]] sf::Vector2f calcRelativePos(const sf::Vector2f& mouse_pos) const;
    void move(const sf::Vector2f& destination, const int delta_time) const;
    void checkMirror(const bool is_angle_in_quadrant2_or3);
    
    ~Wraith() noexcept = default;
    Wraith(Wraith&&) noexcept = default;
    Wraith& operator=(Wraith&&) noexcept = default;
    Wraith(const Wraith&) noexcept = delete;
    Wraith& operator=(const Wraith&) noexcept = delete;
};
