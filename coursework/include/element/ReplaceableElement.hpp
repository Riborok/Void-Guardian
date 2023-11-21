#pragma once
#include "Element.hpp"
#include "../model/polygon/Polygon.hpp"

class ReplaceableElement final : public Element {
    static constexpr size_t START_INDEX = 0;
    
    std::vector<SimpleSprite*> _replaceable_sprites;
    size_t _sprite_index = START_INDEX;
public:
    ReplaceableElement(Polygon *polygon, std::vector<SimpleSprite*> &&z_index_sprites, const size_t id);

    void setSpriteIndex(const size_t sprite_index);

    ~ReplaceableElement() noexcept override;
    
    ReplaceableElement(const ReplaceableElement&) noexcept = delete;
    ReplaceableElement& operator=(const ReplaceableElement&) noexcept = delete;
    ReplaceableElement(ReplaceableElement&&) noexcept = delete;
    ReplaceableElement& operator=(ReplaceableElement&&) noexcept = delete;
};