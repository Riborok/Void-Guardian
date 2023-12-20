#include "../../../../../include/game/entity/component/character/Character.hpp"

Character::Character(ReplaceableElement &element, const CharacterStats &character_stats, const int num) :
    EntityComponent(element, num), _element(&element), _stats(character_stats) {}

Element& Character::getElement() const { return *_element; }

void Character::setSpriteIndex(const size_t sprite_index) const { _element->setSpriteIndex(sprite_index); }

const CharacterStats& Character::getStats() const { return _stats; }