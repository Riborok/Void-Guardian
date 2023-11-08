#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

class SimpleSprite : public sf::Sprite {
    int _z_index;
protected:
    sf::Texture _texture;
public:
    SimpleSprite(const std::string &src, const int z_index);

    bool operator<(const SimpleSprite &other) const;
    bool operator>(const SimpleSprite &other) const;

    ~SimpleSprite() noexcept override = default;
    
    SimpleSprite(const SimpleSprite&) noexcept = delete;
    SimpleSprite& operator=(const SimpleSprite&) noexcept = delete;
    SimpleSprite(SimpleSprite&&) noexcept = delete;
    SimpleSprite& operator=(SimpleSprite&&) noexcept = delete;
};

struct SimpleSpriteCompare final {
    bool operator()(const SimpleSprite *ptr1, const SimpleSprite *ptr2) const;
};