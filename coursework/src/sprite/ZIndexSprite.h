#pragma once
#include <SFML/Graphics/Sprite.hpp>

#include "../game/identifiable/Identifiable.h"

class ZIndexSprite : public sf::Sprite, Identifiable {
    int _z_index;
public:
    explicit ZIndexSprite(const int z_index, const unsigned int id): Identifiable(id), _z_index(z_index) {
    }

    bool operator<(const ZIndexSprite &other) const {
        return _z_index < other._z_index;
    }
    bool operator>(const ZIndexSprite &other) const {
        return _z_index > other._z_index;
    }
    bool operator==(const ZIndexSprite &other) const {
        return _z_index == other._z_index;
    }
    bool operator!=(const ZIndexSprite &other) const {
        return _z_index != other._z_index;
    }

    ~ZIndexSprite() noexcept override = default;
    ZIndexSprite(const ZIndexSprite&) noexcept = default;
    ZIndexSprite& operator=(const ZIndexSprite&) noexcept = default;
    ZIndexSprite(ZIndexSprite&&) noexcept = default;
    ZIndexSprite& operator=(ZIndexSprite&&) noexcept = default;
};
