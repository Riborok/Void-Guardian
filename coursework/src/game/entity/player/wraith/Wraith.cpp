#include "../../../../../include/game/entity/player/wraith/Wraith.hpp"

#include "../../../../../include/geometry/GeomAuxiliaryFunc.hpp"

Wraith::Wraith(ReplaceableElement &element, const WraithStats &wraith_stats) :
    _element(&element), _wraith_stats(wraith_stats){}

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

const WraithStats& Wraith::getStats() const { return _wraith_stats; }