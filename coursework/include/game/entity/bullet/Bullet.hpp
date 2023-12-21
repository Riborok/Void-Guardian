#pragma once
#include "../Entity.hpp"
#include "../component/bullet casing/BulletCasing.hpp"

class Bullet final : public Entity {
    sf::Vector2f _velocity;
    BulletCasing _bullet_casing;
public:
    Bullet(BulletCasing &&bullet_casing, const sf::Vector2f &velocity, const EntityInfo &entity_info);
    [[nodiscard]] sf::Vector2f getVelocity(const int delta_time) const;
    [[nodiscard]] const BulletCasing& getBulletCasing() const;
    
    ~Bullet() noexcept override = default;
    Bullet(const Bullet&) noexcept = delete;
    Bullet& operator=(const Bullet&) noexcept = delete;
    Bullet(Bullet&&) noexcept = delete;
    Bullet& operator=(Bullet&&) noexcept = delete;
};
