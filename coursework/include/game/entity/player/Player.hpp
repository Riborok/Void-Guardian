#pragma once
#include "Control.hpp"
#include "../Entity.hpp"
#include "../../../element/Element.hpp"
#include "gun/Gun.hpp"
#include "wraith/Wraith.hpp"

class Player final : public Entity {
    // TODO: Adjust the gun position for different player characters
    // Currently set for the "Wraith" character; customize based on the active player character
    static constexpr float GUN_POS_INDENT_X = 6;
    static constexpr float GUN_POS_INDENT_Y = 18;
    
    Wraith _wraith;
    Gun _gun;
    Control _control;
public:
    Player(Wraith&& wraith, Gun &&gun, const EntityInfo &entity_info,
        const Control &control = { sf::Keyboard::W, sf::Keyboard::Space });
    
    [[nodiscard]] const Control& getControl() const;
    [[nodiscard]] sf::Vector2f getGunPos() const;
    
    [[nodiscard]] const Wraith &getWraith() const;
    [[nodiscard]] const Gun &getGun() const;
    
    void checkMirror(const bool is_angle_in_quadrant2_or3);

    ~Player() noexcept override = default;
    Player(const Player&) noexcept = delete;
    Player& operator=(const Player&) noexcept = delete;
    Player(Player&&) noexcept = delete;
    Player& operator=(Player&&) noexcept = delete;
};
