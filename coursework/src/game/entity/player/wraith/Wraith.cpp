#include "../../../../../include/game/entity/player/wraith/Wraith.hpp"

Wraith::Wraith(ReplaceableElement &element, const WraithStats &wraith_stats, const int num) :
    _element(&element), _wraith_stats(wraith_stats), _num(num) {}

const Element& Wraith::getElement() const { return *_element; }

void Wraith::setSpriteIndex(const size_t sprite_index) const { _element->setSpriteIndex(sprite_index); }

const WraithStats& Wraith::getStats() const { return _wraith_stats; }

int Wraith::getNum() const { return _num; }