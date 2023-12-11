#include "../../../../../include/game/entity/player/gun/Gun.hpp"

#include "../../../../../include/geometry/Trigonometry.hpp"

Gun::Gun(Element &element, const GunStats &gun_stats, const int num):
    _element(&element), _gun_stats(gun_stats), _num(num) {}

Element& Gun::getElement() const { return *_element; }

bool Gun::canFire() const {
    if (_last_shot_elapsed_time.getElapsedTime().asMilliseconds() >= _gun_stats.reload_time) {
        _last_shot_elapsed_time.restart();
        return true;
    }
    return false;
}

LaunchData Gun::fire() const {
    const auto& polygon = _element->getPolygon();
    const auto& points = polygon.getPoints();
    return _element->isMirroredHor()
        ? LaunchData{points[0], points[0] - points[1], Trigonometry::M_PI_ + polygon.getRotation(), _num}
        : LaunchData{points[1], points[1] - points[0], polygon.getRotation(), _num};
}

size_t Gun::getId() const { return _element->getId(); }

[[nodiscard]] int Gun::geNum() const { return _num; }

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