#pragma once
#include "TransformParams.hpp"
#include "../model/polygon/Polygon.hpp"
#include "../game/identifiable/Identifiable.hpp"
#include "../sprite/SimpleSprite.hpp"

class Element : public Identifiable {
    friend class AnimationExecutor;
    friend class StateChangerForAnimated;
    friend struct ElementCompare;
protected:
    Polygon *_polygon;
    SimpleSprite *_sprite;
    TransformParams _transform_params;

    [[nodiscard]] static bool isMirrored(const float coord);
public:
    Element(Polygon *polygon, SimpleSprite *sprite, const sf::Vector2f &scale, const size_t id);

    [[nodiscard]] float calcRectDiameter() const;
    [[nodiscard]] const Polygon &getPolygon() const;
    [[nodiscard]] const TransformParams &getTransformParams() const;
    [[nodiscard]] bool isMirroredHor() const;
    [[nodiscard]] int getZIndex() const;
    void setZIndex(const int z_index) const;
    
    void mirrorHor();
    void move(const sf::Vector2f &vector) const;
    void rotate(const sf::Vector2f &target, const float delta_angle) const;
    
    void fillSprite(sf::Sprite &sprite) const;
    
    ~Element() noexcept override;
    Element(Element&&) noexcept = delete;
    Element& operator=(Element&&) noexcept = delete;
    Element(const Element&) noexcept = delete;
    Element& operator=(const Element&) noexcept = delete;
};

struct ElementCompare final {
    bool operator()(const Element *ptr1, const Element *ptr2) const;
};

typedef std::vector<const Element*> Elements;