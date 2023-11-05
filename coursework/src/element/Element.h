#pragma once
#include "../game/identifiable/Identifiable.h"
#include "../sprite/SimpleSprite.h"

class Element : public Identifiable {
protected:
    Polygon *_polygon;
    SimpleSprite *_sprite;
public:
    Element(Polygon *polygon, SimpleSprite *sprite, const size_t id)
        : Identifiable(id),
          _polygon(polygon),
          _sprite(sprite) { }
    Polygon &getPolygon() const { return *_polygon; }
    SimpleSprite &getSprite() const { return *_sprite; }
    
    void adjustSpritePosition(const sf::Vector2f &offset) const {
        auto &sprite = getSprite();
        auto &polygon = getPolygon();
        sprite.setPosition(polygon.points()[0] + offset);
    }

    ~Element() noexcept override {
        delete _polygon;
        delete _sprite;
    }
    
    Element(const Element&) = delete;
    Element& operator=(const Element&) = delete;
    Element(Element&&) = delete;
    Element& operator=(Element&&) = delete;
};