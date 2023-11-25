#include "../../../../../include/game/entity/player/gun/Gun.hpp"

#include "../../../../../include/geometry/Trigonometry.hpp"

Gun::Gun(Element &element, const GunInfo &gun_info): _element(&element), _gun_info(gun_info){}

const Element& Gun::getElement() const { return *_element; }

void Gun::mirrorHorizontally() {
    _element->mirrorHorizontally(_is_mirrored);
    _is_mirrored = !_is_mirrored;
}

void Gun::checkMirror(const bool is_angle_in_quadrant2_or3) {
    if ((_is_mirrored && !is_angle_in_quadrant2_or3) || (!_is_mirrored && is_angle_in_quadrant2_or3))
        mirrorHorizontally();
}

bool Gun::isMirror() const { return _is_mirrored; }

void Gun::update(const sf::Vector2f& target_p, const float target_a) const {
    const auto& polygon = _element->getPolygon();
    
    const auto& curr_p = _is_mirrored
        ? polygon.getPoints()[1]
        : polygon.getPoints()[0];
    const float delta_angle = _is_mirrored
        ? Trigonometry::M_PI_ + (target_a - polygon.getRotation())
        : target_a - polygon.getRotation();
    
    _element->move(target_p - curr_p);
    _element->rotate(curr_p, delta_angle);
}
