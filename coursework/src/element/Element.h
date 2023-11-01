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
    void setSpriteIndex(const unsigned int sprite_index) { _sprite_index = sprite_index; }
    Polygon &getPolygon() const { return *_polygon; }
    SimpleSprite &getSprite() const { return *_z_index_sprites[_sprite_index]; }
    
    void adjustSpritePosition(const sf::Vector2u &window_size) const {
        auto &sprite = getSprite();
        auto &polygon = getPolygon();
        
        auto p0 = *polygon.points();
        GeomAuxiliaryFunc::clampVector(p0, window_size);

        sprite.setPosition(p0);
        sprite.setRotation(polygon.getRotation());
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