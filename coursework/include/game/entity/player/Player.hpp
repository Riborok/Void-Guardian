#pragma once
#include "Control.hpp"
#include "../Entity.hpp"
#include "gun/Gun.hpp"
#include "wraith/Wraith.hpp"

class Player final : public Entity {
    static constexpr int GUN_CHANGE_COOLDOWN = 500;
    
    Wraith _wraith;
    Gun _gun;
    Control _control;
    mutable sf::Clock _last_change_elapsed_time;
public:
    Player(Wraith&& wraith, Gun &&gun, const EntityInfo &entity_info, const Control &control);
    
    [[nodiscard]] const Control& getControl() const;
    [[nodiscard]] sf::Vector2f getGunPos() const;
    
    [[nodiscard]] const Wraith &getWraith() const;
    [[nodiscard]] const Gun &getGun() const;
    
    void checkMirror(const bool is_angle_in_quadrant2_or3) const;
    bool canTakeNewGun() const;
    Gun takeNewGun(Gun&& gun);

    ~Player() noexcept override = default;
    Player(const Player&) noexcept = delete;
    Player& operator=(const Player&) noexcept = delete;
    Player(Player&&) noexcept = delete;
    Player& operator=(Player&&) noexcept = delete;
};
