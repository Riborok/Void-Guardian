#pragma once
#include "../game/identifiable/Identifiable.h"
#include "../model/entity/Entity.h"
#include "../sprite/SimpleSprite.h"

class Element final : public Identifiable {
    Entity *_rectangular_entity;
    SimpleSprite *_z_index_sprite;
public:
    Element(Entity *rectangular_entity, SimpleSprite *z_index_sprite, const unsigned int id) : Identifiable(id),
    _rectangular_entity(rectangular_entity), _z_index_sprite(z_index_sprite) { }

    Entity &getEntity() const { return *_rectangular_entity; }
    SimpleSprite &getSprite() const { return *_z_index_sprite; }

    ~Element() noexcept override {
        delete _rectangular_entity;
        delete _z_index_sprite;
    }
    
    Element(const Element&) noexcept = delete;
    Element& operator=(const Element&) noexcept = delete;
    Element(Element&&) noexcept = delete;
    Element& operator=(Element&&) noexcept = delete;
};
