#include "../../include/sprite/SimpleSprite.hpp"

SimpleSprite::SimpleSprite(const std::string &src, const int z_index) : _z_index(z_index) {
    _texture.loadFromFile(src);
    setTexture(_texture);
}

bool SimpleSprite::operator<(const SimpleSprite &other) const {
    return _z_index < other._z_index;
}

bool SimpleSprite::operator>(const SimpleSprite &other) const {
    return _z_index > other._z_index;
}

bool SimpleSpriteCompare::operator()(const SimpleSprite *ptr1, const SimpleSprite *ptr2) const {
    return *ptr1 > *ptr2;
}