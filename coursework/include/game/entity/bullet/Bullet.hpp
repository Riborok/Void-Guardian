#pragma once
#include "BulletInfo.hpp"
#include "../Entity.hpp"
#include "../../../element/Element.hpp"

class Bullet final : public Entity {
    Element *_element;
    sf::Vector2f _velocity;
    BulletStats _bullet_stats;
    int _num;
    
public:
    Bullet(Element &element, const sf::Vector2f &velocity, const BulletInfo &bullet_info, const EntityInfo &entity_info, const int num);
    void move(const sf::Vector2f &velocity) const;
    [[nodiscard]] sf::Vector2f getVelocity(const int delta_time) const;
    [[nodiscard]] const BulletStats &getStats() const;
    [[nodiscard]] int getNum() const;

    [[nodiscard]] const Element& getElement() const;
    
    ~Bullet() noexcept override = default;
    Bullet(const Bullet&) noexcept = delete;
    Bullet& operator=(const Bullet&) noexcept = delete;
    Bullet(Bullet&&) noexcept = delete;
    Bullet& operator=(Bullet&&) noexcept = delete;
};
