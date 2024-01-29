#pragma once
#include <SFML/Graphics.hpp>
#include "SpriteInfo.hpp"

class SimpleSprite {
    int _z_index;
protected:
    sf::IntRect _texture_rect;
    const sf::Texture *_texture;
    SimpleSprite(const SimpleSpriteInfo &simple_sprite_info, const int parts_by_width);
public:
    explicit SimpleSprite(const SimpleSpriteInfo &simple_sprite_info);
    [[nodiscard]] int getZIndex() const;
    void setZIndex(const int z_index);

    void setTextureToSprite(sf::Sprite &sprite) const;
    [[nodiscard]] float getWidth() const;
    [[nodiscard]] float getHeight() const;
    bool operator<(const SimpleSprite &other) const;
    bool operator>(const SimpleSprite &other) const;

    bool operator!=(const sf::Sprite &sprite) const;
    bool operator==(const sf::Sprite &sprite) const;
    
    virtual ~SimpleSprite() noexcept = default;
    
    SimpleSprite(const SimpleSprite&) noexcept = delete;
    SimpleSprite& operator=(const SimpleSprite&) noexcept = delete;
    SimpleSprite(SimpleSprite&&) noexcept = default;
    SimpleSprite& operator=(SimpleSprite&&) noexcept = delete;
};