#include "../../include/element/ReplaceableElement.hpp"

ReplaceableElement::ReplaceableElement(Polygon *polygon, ReplaceableSprites &&z_index_sprites,
        const sf::Vector2f &scale, const size_t id)
    : Element(polygon, z_index_sprites[START_INDEX], scale, id), _replaceable_sprites(std::move(z_index_sprites)) {
}

void ReplaceableElement::setSpriteIndex(const size_t sprite_index) {
    if (_sprite_index != sprite_index) {
        _sprite = _replaceable_sprites[sprite_index];
        _sprite_index = sprite_index;
    }
}

ReplaceableElement::~ReplaceableElement() noexcept {
    for (size_t i = 0; i < _sprite_index; ++i)
        delete _replaceable_sprites[i];
    for (size_t i = _sprite_index + 1; i < _replaceable_sprites.size(); ++i)
        delete _replaceable_sprites[i];
}