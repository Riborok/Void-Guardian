#pragma once
#include "../game/identifiable/Identifiable.h"
#include "../sprite/SimpleSprite.h"

class Element final : public Identifiable {
    Polygon *_polygon;
    std::vector<SimpleSprite*> _z_index_sprites;
    unsigned int _sprite_index = 0;
public:
    Element(Polygon *polygon, const std::vector<SimpleSprite*> &z_index_sprites, const unsigned int id)
        : Identifiable(id),
          _polygon(polygon),
          _z_index_sprites(z_index_sprites) { }
    void setSpriteIndex(const unsigned int sprite_index) {
        if (_sprite_index != sprite_index) {
            const auto &prev_sprite = *_z_index_sprites[_sprite_index];
            auto &curr_sprite = *_z_index_sprites[sprite_index];
            
            curr_sprite.setPosition(prev_sprite.getPosition());
            curr_sprite.setRotation(prev_sprite.getRotation());
            curr_sprite.setOrigin(prev_sprite.getOrigin());
            curr_sprite.setScale(prev_sprite.getScale());
            
            _sprite_index = sprite_index;
        }
    }
    Polygon &getPolygon() const { return *_polygon; }
    SimpleSprite &getSprite() const { return *_z_index_sprites[_sprite_index]; }
    
    void adjustSpritePosition(const sf::Vector2f &offset) const {
        auto &sprite = getSprite();
        auto &polygon = getPolygon();
        sprite.setPosition(*polygon.points() + offset);
    }

    ~Element() noexcept override {
        delete _polygon;
        for (const auto *sprite : _z_index_sprites)
            delete sprite;
    }
    
    Element(const Element&) = delete;
    Element& operator=(const Element&) = delete;
    Element(Element&&) = delete;
    Element& operator=(Element&&) = delete;
};