#pragma once
#include "Control.hpp"
#include "../FightingEntity.hpp"
#include "../component/character/Character.hpp"
#include "../component/gun/Gun.hpp"

class Player final : public FightingEntity {
    static constexpr int GUN_CHANGE_COOLDOWN = 500;
    Control _control;
    mutable sf::Clock _last_change_elapsed_time;
public:
    Player(Character&& character, Gun &&gun, const EntityInfo &entity_info, const sf::Vector2f &gun_offset, const Control &control);
    [[nodiscard]] const Control& getControl() const;
    bool canTakeNewGun() const;

    ~Player() noexcept override = default;
    Player(const Player&) noexcept = delete;
    Player& operator=(const Player&) noexcept = delete;
    Player(Player&&) noexcept = delete;
    Player& operator=(Player&&) noexcept = delete;
};