#include "../../include/sprite/SimpleSprite.hpp"

SimpleSprite::SimpleSprite(const SimpleInfo &simple_info, const int parts_by_width) : _z_index(simple_info.z_index) {
    _texture.loadFromFile(simple_info.src);
    _texture_rect.width = static_cast<int>(_texture.getSize().x) / parts_by_width;
    _texture_rect.height = static_cast<int>(_texture.getSize().y);
}

SimpleSprite::SimpleSprite(const SimpleInfo &simple_info) : _z_index(simple_info.z_index) {
    _texture.loadFromFile(simple_info.src);
    _texture_rect.width = static_cast<int>(_texture.getSize().x);
    _texture_rect.height = static_cast<int>(_texture.getSize().y);
}

sf::Vector2f SimpleSprite::getSize() const {
    return {static_cast<float>(_texture_rect.width), static_cast<float>(_texture_rect.height)};
}

float SimpleSprite::getWidth() const {
    return static_cast<float>(_texture_rect.width);
}

float SimpleSprite::getHeight() const {
    return static_cast<float>(_texture_rect.height);
}

void SimpleSprite::setTexture(sf::Sprite &sprite) const {
    sprite.setTextureRect(_texture_rect);
    sprite.setTexture(_texture);
}

bool SimpleSprite::operator<(const SimpleSprite &other) const {
    return _z_index < other._z_index;
}

bool SimpleSprite::operator>(const SimpleSprite &other) const {
    return _z_index > other._z_index;
}