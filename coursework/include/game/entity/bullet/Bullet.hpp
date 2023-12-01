#pragma once
#include "BulletInfo.hpp"
#include "../Entity.hpp"
#include "../../../element/Element.hpp"

class Bullet final : public Entity {
    Element *_element;
    sf::Vector2f _velocity;
    BulletStats _bullet_stats;

public:
    Bullet(Element &element, const sf::Vector2f &velocity, const BulletInfo &bullet_info, const EntityInfo &entity_info);
    void move(const int delta_time) const;
    void appendElements(Elements &elements) const override;
    [[nodiscard]] const BulletStats &getStats() const;
    
    ~Bullet() noexcept override = default;
    Bullet(const Bullet&) noexcept = delete;
    Bullet& operator=(const Bullet&) noexcept = delete;
    Bullet(Bullet&&) noexcept = delete;
    Bullet& operator=(Bullet&&) noexcept = delete;
};
