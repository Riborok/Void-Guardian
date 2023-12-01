#pragma once
#include "GunInfo.hpp"
#include "LaunchData.hpp"
#include "../../../../element/Element.hpp"

class Gun final {
    Element *_element;
    GunStats _gun_stats;
    int _num;
    sf::Clock _shot_clock;

    bool _is_mirrored = false;
    void mirrorHorizontally();
public:
    Gun(Element &element, const GunStats &gun_stats, const int num);
    [[nodiscard]] const Element& getElement() const;
    void update(const sf::Vector2f& target_p, const float target_a) const;
    void checkMirror(const bool is_angle_in_quadrant2_or3);
    [[nodiscard]] bool isMirror() const;
    [[nodiscard]] bool fire(LaunchData &launch_data);
    
    ~Gun() noexcept = default;
    Gun(Gun&&) noexcept = default;
    Gun& operator=(Gun&&) noexcept = default;
    Gun(const Gun&) noexcept = delete;
    Gun& operator=(const Gun&) noexcept = delete;
};
