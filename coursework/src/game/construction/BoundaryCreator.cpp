// ReSharper disable CppExpressionWithoutSideEffects CppNoDiscardExpression
#include "../../../include/game/construction/BoundaryCreator.hpp"

#include "../../../include/additionally/AdditionalFunc.hpp"
#include "../../../include/additionally/Constants.hpp"
#include "../../../include/element/ElementCreation.hpp"
#include "../../../include/game/construction/LocationCreation.hpp"

int BoundaryCreator::createHorBoundary(int coord, const int last, const int y) const {
    while (coord < last) {
        _quadtree->insert(ElementCreation::create({static_cast<float>(coord), static_cast<float>(y)},
            0, ElementTypes::BLOCK, _num, _scale));
        coord += _delta.x;
    }
    return coord;
}

int BoundaryCreator::createHorMissedBlocks(int coord, const int last, const int y, Location *location) {
    while (coord < last) {
        location->addMissedBlock(ElementCreation::create({static_cast<float>(coord), static_cast<float>(y)},
            0, ElementTypes::BLOCK, AdditionalFunc::getRandom(_missed_blocks_num), _scale));
        coord += _delta.x;
    }
    return coord;
}

int BoundaryCreator::createVertBoundary(int coord, const int last, const int x) const {
    while (coord < last) {
        _quadtree->insert(ElementCreation::create({static_cast<float>(x), static_cast<float>(coord)},
            0, ElementTypes::BLOCK, _num, _scale));
        coord += _delta.y;
    }
    return coord;
}

int BoundaryCreator::createVertMissedBlocks(int coord, const int last, const int x, Location *location) {
    while (coord < last) {
        location->addMissedBlock(ElementCreation::create({static_cast<float>(x), static_cast<float>(coord)},
            0, ElementTypes::BLOCK, AdditionalFunc::getRandom(_missed_blocks_num), _scale));
        coord += _delta.y;
    }
    return coord;
}

void BoundaryCreator::createHorBoundaryWithDoor(const sf::Vector2i &p, const int last, Location *location, const int door_size) {
    int coord = p.x;
    const int last_offset = (p.x + last - door_size) / 2;

    coord = createHorBoundary(coord, last_offset, p.y);
    coord = createHorMissedBlocks(coord, coord + door_size, p.y, location);
    createHorBoundary(coord, last, p.y);
}

void BoundaryCreator::createVertBoundaryWithDoor(const sf::Vector2i &p, const int last, Location *location, const int door_size) {
    int coord = p.y;
    const int last_offset = (p.y + last - door_size) / 2;

    coord = createVertBoundary(coord, last_offset, p.x);
    coord = createVertMissedBlocks(coord, coord + door_size, p.x, location);
    createVertBoundary(coord, last, p.x);
}

BoundaryCreator::BoundaryCreator(const int num, const sf::Vector2f &scale,
    const sf::Vector2i &door_count_size, QuadtreeEl &quadtree) :
        _num(num), _scale(scale), _delta(AdditionalFunc::getScaledSize(Constants::BLOCK_SIZE, scale)),
        _door_size(door_count_size.x * _delta.x, door_count_size.y * _delta.y), _quadtree(&quadtree){ }

Location *BoundaryCreator::createLocation(const sf::Vector2i &p0, const sf::Vector2i &p1,
        const DoorOpeningMask door_opening) {
    const int start_x = p0.x + _delta.x;
    const int start_y = p0.y + _delta.y;
    const int last_x = p1.x - _delta.x;
    const int last_y = p1.y - _delta.y;

    const auto location = LocationCreation::create(start_x, start_y, last_x, last_y);

    if (hasLeftDoor(door_opening))   createVertBoundaryWithDoor({p0.x, start_y}, last_y, location, _door_size.y);
    else                             createVertBoundary(start_y, last_y, p0.x);

    if (hasRightDoor(door_opening))  createVertBoundaryWithDoor({last_x, start_y}, last_y, location, _door_size.y);
    else                             createVertBoundary(start_y, last_y, last_x);
    
    if (hasTopDoor(door_opening))    createHorBoundaryWithDoor(p0, p1.x, location, _door_size.x);
    else                             createHorBoundary(p0.x, p1.x, p0.y);

    if (hasBottomDoor(door_opening)) createHorBoundaryWithDoor({p0.x, last_y}, p1.x, location,_door_size.x);
    else                             createHorBoundary(p0.x, p1.x, last_y);
    
    return location;
}

Location *BoundaryCreator::createLocation(const sf::Vector2i &p0, const int count_x, const int count_y,
        const DoorOpeningMask door_opening) {
    const sf::Vector2i p1(p0.x + _delta.x * count_x, p0.y + _delta.y * count_y);
    return createLocation(p0, p1, door_opening);
}

int BoundaryCreator::createVertTransition(const sf::Vector2i &p0, const int last_y) const {
    const int last_x = p0.x + _door_size.x + _delta.x;
    
    createVertBoundary(p0.y, last_y, p0.x);
    createVertBoundary(p0.y, last_y, last_x);
    return last_x + _delta.x;
}

int BoundaryCreator::createHorTransition(const sf::Vector2i &p0, const int last_x) const {
    const int last_y = p0.y + _door_size.y + _delta.y;
    
    createHorBoundary(p0.x, last_x, p0.y);
    createHorBoundary(p0.x, last_x, last_y);
    return last_y + _delta.y;
}

const sf::Vector2i &BoundaryCreator::getDelta() const { return _delta; }