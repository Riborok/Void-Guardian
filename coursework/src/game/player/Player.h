#pragma once
#include "../../additionally/Types.h"
#include "../../element/Element.h"
#include "../../geometry/GeomAuxiliaryFunc.h"
#include "../../geometry/Trigonometry.h"
#include "../../model/polygon/ManipulationOfPolygon.h"

class Player final {
    Element *_element;
    Types::Control _control;
    float _speed;
    bool _is_mirrored = false;

    void restoreMirror() {
        auto &sprite = _element->getSprite();
        sprite.setOrigin(0.0f, 0.0f);
        sprite.setScale(-sprite.getScale().x, sprite.getScale().y);     
        _is_mirrored = false;
    }
    void mirrorHorizontally() {
        auto &sprite = _element->getSprite();
        sprite.setOrigin(static_cast<float>(sprite.getTextureRect().width), 0.0f);
        sprite.setScale(-sprite.getScale().x, sprite.getScale().y);
        _is_mirrored = true;
    }
    void checkMirror(const bool is_angle_in_quadrant2_or3) {
        if (_is_mirrored) {
            if (!is_angle_in_quadrant2_or3)
                restoreMirror();    
        }
        else {
            if (is_angle_in_quadrant2_or3)
                mirrorHorizontally();
        }
    }
    sf::Vector2f calcCenter() const {
        const auto &polygon = _element->getPolygon();
        const auto &position = _element->getSprite().getPosition();
        return { position.x + polygon.getBoundingRectangleHeight() / 2,
            position.y + polygon.getBoundingRectangleHeight() / 2};
    }
public:
    Player(Element &element, const Types::Control &control, const float speed) :
        _element(&element), _control(control), _speed(speed) { }

    void move(const sf::Vector2f &destination, const int delta_time) {
        sf::Vector2f direction_vector = destination - calcCenter();
        GeomAuxiliaryFunc::setLength(direction_vector, _speed * static_cast<float>(delta_time));
        
        checkMirror(Trigonometry::isAngleInQuadrant2Or3(direction_vector));

        ManipulationOfPolygon::movePolygon(_element->getPolygon(), direction_vector);
    }
    void setSpriteIndex(const unsigned int sprite_index) const { _element->setSpriteIndex(sprite_index); }
    
    const Types::Control &getControl() const { return _control; }

    ~Player() noexcept = default;
    
    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;
    Player(Player&&) = delete;
    Player& operator=(Player&&) = delete;
};
