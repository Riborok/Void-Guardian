#include "../../../../../include/game/entity/component/gun/Gun.hpp"
#include "../../../../../include/geometry/Trigonometry.hpp"

Gun::Gun(Element &element, const GunInfo &gun_info, const size_t num):
    EntityComponent(num, element.getId()), _element(&element), _gun_info(gun_info) {}

Element& Gun::getElement() const { return *_element; }

const sf::Vector2f& Gun::getCenterOffset() const { return _gun_info.gun_properties.owner_center_offset; }

bool Gun::canFire() const {
    if (_last_shot_elapsed_time.getElapsedTime().asMilliseconds() >= _gun_info.gun_properties.reload_time) {
        _last_shot_elapsed_time.restart();
        return true;
    }
    return false;
}

LaunchData Gun::fire() const {
    const auto& polygon = _element->getPolygon();
    const auto& points = polygon.getPoints();
    return _element->isMirroredHor()
        ? LaunchData{_gun_info.bullet_multipliers, points[0], points[0] - points[1], Trigonometry::M_PI_ + polygon.getRotation(), _num}
        : LaunchData{_gun_info.bullet_multipliers, points[1], points[1] - points[0], polygon.getRotation(), _num};
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