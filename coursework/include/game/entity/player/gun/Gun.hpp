#pragma once
#include "GunInfo.hpp"
#include "LaunchData.hpp"
#include "../../../../element/Element.hpp"

class Gun final {
    Element *_element;
    GunStats _gun_stats;
    int _num;
    mutable sf::Clock _last_shot_elapsed_time;
public:
    Gun(Element &element, const GunStats &gun_stats, const int num);
    [[nodiscard]] Element& getElement() const;
    void update(const sf::Vector2f& target_p, const float target_a) const;
    [[nodiscard]] bool canFire() const;
    [[nodiscard]] LaunchData fire() const;
    [[nodiscard]] size_t getId() const;
    [[nodiscard]] int geNum() const;
    
    ~Gun() noexcept = default;
    Gun(Gun&&) noexcept = default;
    Gun& operator=(Gun&&) noexcept = default;
    Gun(const Gun&) noexcept = delete;
    Gun& operator=(const Gun&) noexcept = delete;
};