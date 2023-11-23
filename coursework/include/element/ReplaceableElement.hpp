#pragma once
#include "Element.hpp"
#include "../model/polygon/Polygon.hpp"

typedef std::vector<SimpleSprite*> ReplaceableSprites;

class ReplaceableElement final : public Element {
    static constexpr size_t START_INDEX = 0;
    
    ReplaceableSprites _replaceable_sprites;
    size_t _sprite_index = START_INDEX;
public:
    ReplaceableElement(Polygon *polygon, ReplaceableSprites &&z_index_sprites, const sf::Vector2f &scale, const size_t id);

    void setSpriteIndex(const size_t sprite_index);

    ~ReplaceableElement() noexcept override;
    
    ReplaceableElement(const ReplaceableElement&) noexcept = delete;
    ReplaceableElement& operator=(const ReplaceableElement&) noexcept = delete;
    ReplaceableElement(ReplaceableElement&&) noexcept = delete;
    ReplaceableElement& operator=(ReplaceableElement&&) noexcept = delete;
};