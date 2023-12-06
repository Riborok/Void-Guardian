#pragma once
#include "GunInfo.hpp"
#include "LaunchData.hpp"
#include "../../../../element/Element.hpp"

class Gun final {
    friend class Player;
    
    Element *_element;
    GunStats _gun_stats;
    int _num;
    mutable sf::Clock _shot_clock;
public:
    Gun(Element &element, const GunStats &gun_stats, const int num);
    [[nodiscard]] const Element& getElement() const;
    void update(const sf::Vector2f& target_p, const float target_a) const;
    [[nodiscard]] bool fire(LaunchData &launch_data) const;
    
    ~Gun() noexcept = default;
    Gun(Gun&&) noexcept = default;
    Gun& operator=(Gun&&) noexcept = default;
    Gun(const Gun&) noexcept = delete;
    Gun& operator=(const Gun&) noexcept = delete;
};
