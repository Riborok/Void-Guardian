﻿#include "../../../../../include/game/entity/player/gun/Gun.hpp"

#include "../../../../../include/geometry/Trigonometry.hpp"

Gun::Gun(Element &element, const GunStats &gun_stats, const int num):
    _element(&element), _gun_stats(gun_stats), _num(num) {}

const Element& Gun::getElement() const { return *_element; }

bool Gun::fire(LaunchData &launch_data) const {
    if (_shot_clock.getElapsedTime().asMilliseconds() >= _gun_stats.reload_time) {
        _shot_clock.restart();

        const auto& polygon = _element->getPolygon();
        const auto& points = polygon.getPoints();
        launch_data = _element->isMirroredHor()
            ? LaunchData{points[0], points[0] - points[1], Trigonometry::M_PI_ + polygon.getRotation(), _num}
            : LaunchData{points[1], points[1] - points[0], polygon.getRotation(), _num};
        return true;
    }

    return false;
}

void Gun::update(const sf::Vector2f& target_p, const float target_a) const {
    const auto& polygon = _element->getPolygon();
    const bool is_mirrored = _element->isMirroredHor();
    
    const auto& curr_p = is_mirrored
        ? polygon.getPoints()[1]
        : polygon.getPoints()[0];
    const float delta_angle = is_mirrored
        ? Trigonometry::M_PI_ + (target_a - polygon.getRotation())
        : target_a - polygon.getRotation();
    
    _element->move(target_p - curr_p);
    _element->rotate(curr_p, delta_angle);
}
