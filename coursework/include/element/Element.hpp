#pragma once
#include "../model/polygon/Polygon.hpp"
#include "../game/identifiable/Identifiable.hpp"
#include "../sprite/SimpleSprite.hpp"

class Element : public Identifiable {
    friend class SpriteStateExecutor;
protected:
    Polygon *_polygon;
    SimpleSprite *_sprite;
public:
    Element(Polygon *polygon, SimpleSprite *sprite, const size_t id);
    [[nodiscard]] const Polygon &getPolygon() const;
    [[nodiscard]] const SimpleSprite &getSprite() const;
    void move(const sf::Vector2f &vector) const;
    void mirrorHorizontally(const bool is_mirrored) const;
    
    ~Element() noexcept override;
    
    Element(const Element&) noexcept = delete;
    Element& operator=(const Element&) noexcept = delete;
    Element(Element&&) noexcept = delete;
    Element& operator=(Element&&) noexcept = delete;
};