#include "../../include/sprite/SimpleSprite.hpp"

SimpleSprite::SimpleSprite(const SimpleInfo &simple_info, const int parts_by_width):
        _z_index(simple_info.z_index), _texture(&simple_info.texture) {
    const auto texture_size = _texture->getSize();
    _texture_rect.width = static_cast<int>(texture_size.x) / parts_by_width;
    _texture_rect.height = static_cast<int>(texture_size.y);
}

SimpleSprite::SimpleSprite(const SimpleInfo &simple_info):
        _z_index(simple_info.z_index), _texture(&simple_info.texture) {
    const auto texture_size = _texture->getSize();
    _texture_rect.width = static_cast<int>(texture_size.x);
    _texture_rect.height = static_cast<int>(texture_size.y);
}

int SimpleSprite::getZIndex() const { return _z_index; }

void SimpleSprite::setZIndex(const int z_index) { _z_index = z_index; }

float SimpleSprite::getWidth() const {
    return static_cast<float>(_texture_rect.width);
}

float SimpleSprite::getHeight() const {
    return static_cast<float>(_texture_rect.height);
}

void SimpleSprite::setTexture(sf::Sprite &sprite) const {
    sprite.setTextureRect(_texture_rect);
    sprite.setTexture(*_texture);
}

bool SimpleSprite::operator<(const SimpleSprite &other) const {
    return _z_index < other._z_index;
}

bool SimpleSprite::operator>(const SimpleSprite &other) const {
    return _z_index > other._z_index;
}