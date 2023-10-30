#pragma once
#include "../game/identifiable/Identifiable.h"
#include "../model/entity/Entity.h"
#include "../sprite/SimpleSprite.h"

class Element final : public Identifiable {
    Entity *_entity;
    std::vector<SimpleSprite*> _z_index_sprites;
    unsigned int _sprite_index = 0;
public:
    Element(Entity *entity, const std::vector<SimpleSprite*> &z_index_sprites, const unsigned int id)
        : Identifiable(id),
          _entity(entity),
          _z_index_sprites(z_index_sprites) { }

    void setSpriteIndex(const unsigned int sprite_index) {
        _z_index_sprites[sprite_index]->setPosition(_z_index_sprites[_sprite_index]->getPosition());
        _z_index_sprites[sprite_index]->setRotation(_z_index_sprites[_sprite_index]->getRotation());
        
        _sprite_index = sprite_index;
    }
    Entity& getEntity() const { return *_entity; }
    SimpleSprite& getSprite() const { return *_z_index_sprites[_sprite_index]; }

    ~Element() noexcept override {
        delete _entity;
        for (const auto *sprite : _z_index_sprites)
            delete sprite;
    }
    
    Element(const Element&) = delete;
    Element& operator=(const Element&) = delete;
    Element(Element&&) = delete;
    Element& operator=(Element&&) = delete;
};