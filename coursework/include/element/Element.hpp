#pragma once
#include "../model/polygon/Polygon.hpp"
#include "../game/identifiable/Identifiable.hpp"
#include "../sprite/SimpleSprite.hpp"

class Element : public Identifiable {
protected:
    Polygon *_polygon;
    SimpleSprite *_sprite;
public:
    Element(Polygon *polygon, SimpleSprite *sprite, const size_t id);
    [[nodiscard]] Polygon &getPolygon() const;
    [[nodiscard]] SimpleSprite &getSprite() const;
    
    void adjustSpritePosition(const sf::Vector2f &offset) const;

    ~Element() noexcept override;
    
    Element(const Element&) = delete;
    Element& operator=(const Element&) = delete;
    Element(Element&&) = delete;
    Element& operator=(Element&&) = delete;
};