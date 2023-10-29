#pragma once
#include "../game/identifiable/Identifiable.h"
#include "../model/entity/Entity.h"
#include "../sprite/SimpleSprite.h"

class Element final : public Identifiable {
    Entity *_rectangular_entity;
    std::vector<SimpleSprite*> _z_index_sprites;
    unsigned int _sprite_position = 0;
public:
    Element(Entity *rectangular_entity, const std::vector<SimpleSprite*> &z_index_sprites, const unsigned int id)
        : Identifiable(id),
          _rectangular_entity(rectangular_entity),
          _z_index_sprites(z_index_sprites) { }

    void setSpritePosition(const unsigned int position) { _sprite_position = position; }
    Entity& getEntity() const { return *_rectangular_entity; }
    SimpleSprite& getSprite() const { return *_z_index_sprites[_sprite_position]; }

    ~Element() noexcept override {
        delete _rectangular_entity;
        for (const auto *sprite : _z_index_sprites)
            delete sprite;
    }
    
    Element(const Element&) = delete;
    Element& operator=(const Element&) = delete;
    Element(Element&&) = delete;
    Element& operator=(Element&&) = delete;
};