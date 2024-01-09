#pragma once
#include <SFML/Graphics/Sprite.hpp>

#include "AnimatedSprites.hpp"
#include "CharacterText.hpp"
#include "../../sprite/AnimatedSprite.hpp"

class CharacterVisualization final {
    static constexpr float SCALE_MULTIPLIER = 3.5f;
    AnimatedSprites _sprites;
    CharacterInfos *_character_infos;
    CharacterText _character_text;
    sf::Sprite _sprite;
    float _y_start = 0.0f;
    
    sf::Vector2f getSpriteScale(const size_t index) const;
    sf::Vector2f maxSpriteScaledSize() const;
public:
    CharacterVisualization(AnimatedSprites&& sprites, CharacterInfos &character_infos, const sf::Font& font);
    
    void setSpriteParameters(const size_t index);
    void updateSprite(const size_t index, const int delta_time);
    void setPositions(const float x_center, const float y_start, const float button_spacing);
    void draw(sf::RenderWindow &window) const;
    size_t getLastIndex() const;

    ~CharacterVisualization() noexcept = default;
    CharacterVisualization(CharacterVisualization&&) noexcept = default;
    CharacterVisualization& operator=(CharacterVisualization&&) noexcept = delete;
    CharacterVisualization(const CharacterVisualization&) noexcept = delete;
    CharacterVisualization& operator=(const CharacterVisualization&) noexcept = delete;
};