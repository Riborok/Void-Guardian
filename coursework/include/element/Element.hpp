#pragma once
#include "TransformParams.hpp"
#include "../model/polygon/Polygon.hpp"
#include "../game/identifiable/Identifiable.hpp"
#include "../sprite/SimpleSprite.hpp"

class Element : public Identifiable {
    friend class SpriteStateExecutor;
    friend struct ElementCompare;
protected:
    Polygon *_polygon;
    SimpleSprite *_sprite;
    TransformParams _transform_params;
public:
    Element(Polygon *polygon, SimpleSprite *sprite, const sf::Vector2f &scale, const size_t id);
    [[nodiscard]] const Polygon &getPolygon() const;
    void move(const sf::Vector2f &vector) const;
    void rotate(const sf::Vector2f &target, const float delta_angle) const;
    void mirrorHorizontally(const bool is_mirrored);
    void fillSprite(sf::Sprite &sprite) const;
    
    ~Element() noexcept override;
    
    Element(const Element&) noexcept = delete;
    Element& operator=(const Element&) noexcept = delete;
    Element(Element&&) noexcept = delete;
    Element& operator=(Element&&) noexcept = delete;
};

struct ElementCompare final {
    bool operator()(const Element *ptr1, const Element *ptr2) const;
};