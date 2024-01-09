#include "../../../include/game/choose character/CharacterVisualization.hpp"

#include "../../../include/additionally/PixelConverter.hpp"
#include "../../../include/geometry/SizeUtils.hpp"

sf::Vector2f CharacterVisualization::getSpriteScale(const size_t index) const {
    const auto& scale = (*_character_infos)[index].scale;
    return {
        scale.x * PixelConverter::convertWidthToCurrentScreen(SCALE_MULTIPLIER),
        scale.y * PixelConverter::convertHeightToCurrentScreen(SCALE_MULTIPLIER)
    };
}

CharacterVisualization::CharacterVisualization(AnimatedSprites&& sprites, CharacterInfos& character_infos, const sf::Font& font):
    _sprites(std::move(sprites)), _character_infos(&character_infos), _character_text(font){}

sf::Vector2f CharacterVisualization::maxSpriteScaledSize() const {
    sf::Vector2f result{0, 0};
    const auto size(_sprites.size());
    for (size_t i = 0; i < size; ++i) {
        const auto scaled_size(SizeUtils::getScaledSize(sf::Vector2f{_sprites[i].getWidth(),
            _sprites[i].getHeight()}, getSpriteScale(i)));
        if (result.x < scaled_size.x) { result.x = scaled_size.x; }
        if (result.y < scaled_size.y) { result.y = scaled_size.y; }
    }
    return result;
}

void CharacterVisualization::setSpriteParameters(const size_t index) {
    _character_text.fillText((*_character_infos)[index]);
    const auto& animated_sprite(_sprites[index]);
    
    const sf::Vector2f size(animated_sprite.getWidth(), animated_sprite.getHeight());
    const auto scale(getSpriteScale(index));
    const auto scaled_size(SizeUtils::getScaledSize(size, scale));
    
    _sprite.setOrigin(size / 2.0f);
    _sprite.setPosition(_sprite.getPosition().x, _y_start - scaled_size.y / 2.0f);
    _sprite.setScale(scale);
}

void CharacterVisualization::updateSprite(const size_t index, const int delta_time) {
    auto& animated_sprite(_sprites[index]);
    if (animated_sprite != _sprite)
        setSpriteParameters(index);
    
    animated_sprite.changeState(delta_time);
    animated_sprite.setTextureToSprite(_sprite);
}

void CharacterVisualization::setPositions(const float x_center, const float y_start, const float button_spacing) {
    _y_start = y_start;
    _sprite.setPosition(x_center, y_start);
    const auto max_sprite_scaled_size(maxSpriteScaledSize());
    _character_text.setPosition({x_center + max_sprite_scaled_size.x, y_start - max_sprite_scaled_size.y}, button_spacing);
}

size_t CharacterVisualization::getLastIndex() const { return _sprites.size() - 1; }

void CharacterVisualization::draw(sf::RenderWindow &window) const {
    window.draw(_sprite);
    _character_text.draw(window);
}