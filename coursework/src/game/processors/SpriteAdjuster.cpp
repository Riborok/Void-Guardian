#include "../../../include/game/processors/SpriteAdjuster.hpp"

SpriteAdjuster::SpriteAdjuster(std::unordered_set<Element*, IdentifiableHash> &elements, sf::Vector2f &offset)
    : _elements(&elements), _offset(&offset) { }

void SpriteAdjuster::adjustPositions() const {
    for (const auto *element : *_elements)
        element->adjustSpritePosition(*_offset);
}