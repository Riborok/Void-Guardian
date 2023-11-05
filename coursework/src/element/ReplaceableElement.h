#pragma once
#include "Element.h"
#include "../model/polygon/Polygon.h"

constexpr size_t START_INDEX = 0;

class ReplaceableElement final : public Element {
    std::vector<SimpleSprite*> _replaceable_sprites;
    size_t _sprite_index = START_INDEX;
public:
    ReplaceableElement(Polygon *polygon, std::vector<SimpleSprite*> &z_index_sprites, const size_t id) :
        Element(polygon, z_index_sprites[START_INDEX], id), _replaceable_sprites(std::move(z_index_sprites)){ }
    
    void setSpriteIndex(const size_t sprite_index) {
        if (_sprite_index != sprite_index) {
            const auto &prev_sprite = *_replaceable_sprites[_sprite_index];
            _sprite = _replaceable_sprites[sprite_index];
            auto &curr_sprite = *_replaceable_sprites[sprite_index];
            
            curr_sprite.setPosition(prev_sprite.getPosition());
            curr_sprite.setRotation(prev_sprite.getRotation());
            curr_sprite.setOrigin(prev_sprite.getOrigin());
            curr_sprite.setScale(prev_sprite.getScale());
            
            _sprite_index = sprite_index;
        }
    }
    
    ~ReplaceableElement() noexcept override {
        for (size_t i = 0; i < _sprite_index; ++i)
            delete _replaceable_sprites[i];
        for (size_t i = _sprite_index + 1; i < _replaceable_sprites.size(); ++i)
            delete _replaceable_sprites[i];
    }
    
    ReplaceableElement(const ReplaceableElement&) = delete;
    ReplaceableElement& operator=(const ReplaceableElement&) = delete;
    ReplaceableElement(ReplaceableElement&&) = delete;
    ReplaceableElement& operator=(ReplaceableElement&&) = delete;
};