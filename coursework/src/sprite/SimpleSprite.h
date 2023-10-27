#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "ZIndexSprite.h"

enum SimpleSpriteType {
    GUN = 0,  
};

class SimpleSprite final : public ZIndexSprite {
    static const std::string SRC[][1];
    
    sf::Texture _texture;
public:
    SimpleSprite(const SimpleSpriteType type, const int num, const int z_index, const unsigned int id): ZIndexSprite(z_index, id){
        _texture.loadFromFile(SRC[type][num]);
        
        setTexture(_texture);
    }

    ~SimpleSprite() noexcept override = default;
    SimpleSprite(const SimpleSprite&) noexcept = default;
    SimpleSprite& operator=(const SimpleSprite&) noexcept = default;
    SimpleSprite(SimpleSprite&&) noexcept = default;
    SimpleSprite& operator=(SimpleSprite&&) noexcept = default;
};

const std::string SimpleSprite::SRC[][1] = {
    {
        "./img/Guns/Gun_0.png",
    },
};