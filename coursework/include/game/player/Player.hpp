#pragma once
#include "../../additionally/Types.hpp"
#include "../../element/Element.hpp"
#include "../../element/ReplaceableElement.hpp"
#include "../../geometry/GeomAuxiliaryFunc.hpp"

class Player {
    ReplaceableElement* _element;
    Types::Control _control;
    float _speed;
    bool _is_mirrored;

    void restoreMirror();
    void mirrorHorizontally();
    void checkMirror(const bool is_angle_in_quadrant2_or3);
    [[nodiscard]] sf::Vector2f calcCenter() const;

public:
    Player(ReplaceableElement& element, const Types::Control& control, const float speed);

    void move(const sf::Vector2f& destination, const int delta_time);
    void setSpriteIndex(const size_t sprite_index) const;

    [[nodiscard]] const Types::Control& getControl() const;
    [[nodiscard]] Element& getElement() const;

    ~Player() noexcept = default;
    
    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;
    Player(Player&&) = delete;
    Player& operator=(Player&&) = delete;
};
