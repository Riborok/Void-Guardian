#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

class SimpleSprite : public sf::Sprite {
    int _z_index;
protected:
    sf::Texture _texture;
public:
    SimpleSprite(const std::string &src, const int z_index): _z_index(z_index){
        _texture.loadFromFile(src);
        setTexture(_texture);
    }

    bool operator<(const SimpleSprite &other) const {
        return _z_index < other._z_index;
    }
    bool operator>(const SimpleSprite &other) const {
        return _z_index > other._z_index;
    }
    bool operator==(const SimpleSprite &other) const {
        return _z_index == other._z_index;
    }
    bool operator!=(const SimpleSprite &other) const {
        return _z_index != other._z_index;
    }

    ~SimpleSprite() noexcept override = default;
    
    SimpleSprite(const SimpleSprite&) noexcept = delete;
    SimpleSprite& operator=(const SimpleSprite&) noexcept = delete;
    SimpleSprite(SimpleSprite&&) noexcept = delete;
    SimpleSprite& operator=(SimpleSprite&&) noexcept = delete;
};