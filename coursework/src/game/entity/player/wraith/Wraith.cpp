#include "../../../../../include/game/entity/player/wraith/Wraith.hpp"

#include "../../../../../include/geometry/GeomAuxiliaryFunc.hpp"
#include "../../../../../include/geometry/Trigonometry.hpp"

Wraith::Wraith(ReplaceableElement &element, const WraithInfo &wraith_info) :
    _element(&element), _wraith_info(wraith_info){}

const Element& Wraith::getElement() const { return *_element; }

void Wraith::setSpriteIndex(const size_t sprite_index) const { _element->setSpriteIndex(sprite_index); }

void Wraith::mirrorHorizontally() {
    _element->mirrorHorizontally(_is_mirrored);
    _is_mirrored = !_is_mirrored;
}

void Wraith::checkMirror(const bool is_angle_in_quadrant2_or3) {
    if ((_is_mirrored && !is_angle_in_quadrant2_or3) || (!_is_mirrored && is_angle_in_quadrant2_or3))
        mirrorHorizontally();
}

sf::Vector2f Wraith::getDestination(const sf::Vector2f& mouse_pos) const {
    return mouse_pos - _element->getPolygon().calcCenter();
}

void Wraith::move(const sf::Vector2f& destination, const int delta_time) const {
    sf::Vector2f direction_vector(destination);
    GeomAuxiliaryFunc::setLength(direction_vector, _wraith_info.speed * static_cast<float>(delta_time));
    
    _element->move(direction_vector);
}
