#pragma once
#include "GunInfo.hpp"
#include "LaunchData.hpp"
#include "../../EntityComponent.hpp"
#include "../../../../element/Element.hpp"

class Gun final : public EntityComponent {
    Element *_element;
    GunStats _gun_stats;
    mutable sf::Clock _last_shot_elapsed_time;
public:
    Gun(Element &element, const GunStats &gun_stats, const int num);
    void update(const sf::Vector2f& target_p, const float target_a) const;
    [[nodiscard]] Element& getElement() const;
    [[nodiscard]] bool canFire() const;
    [[nodiscard]] LaunchData fire() const;
    
    ~Gun() noexcept override = default;
    Gun(Gun&&) noexcept = default;
    Gun& operator=(Gun&&) noexcept = default;
    Gun(const Gun&) noexcept = delete;
    Gun& operator=(const Gun&) noexcept = delete;
};