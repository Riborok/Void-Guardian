// ReSharper disable CppExpressionWithoutSideEffects CppNoDiscardExpression
#include "../../../include/game/construction/BoundaryCreator.hpp"

#include "../../../include/additionally/AdditionalFunc.hpp"
#include "../../../include/game/construction/LocationCreator.hpp"
#include "../../../include/geometry/GeomAuxiliaryFunc.hpp"

int BoundaryCreator::createHorBoundary(int coord, const int last, const int y) const {
    while (coord < last) {
        _quadtree->insert(_element_creator->create({
            {static_cast<float>(coord), static_cast<float>(y)},
            0, ElementType::BLOCK, _building_data.num, _building_data.scale}));
        coord += _building_data.delta.x;
    }
    return coord;
}

int BoundaryCreator::createHorMissedBlocks(int coord, const int last, const int y, Location *location) {
    while (coord < last) {
        location->addMissedBlock(_element_creator->create({
            {static_cast<float>(coord), static_cast<float>(y)},
            0, ElementType::BLOCK, AdditionalFunc::getRandom(_missed_blocks_num),
            _building_data.scale}));
        coord += _building_data.delta.x;
    }
    return coord;
}

int BoundaryCreator::createVertBoundary(int coord, const int last, const int x) const {
    while (coord < last) {
        _quadtree->insert(_element_creator->create({
            {static_cast<float>(x), static_cast<float>(coord)},
            0, ElementType::BLOCK, _building_data.num, _building_data.scale}));
        coord += _building_data.delta.y;
    }
    return coord;
}

int BoundaryCreator::createVertMissedBlocks(int coord, const int last, const int x, Location *location) {
    while (coord < last) {
        location->addMissedBlock(_element_creator->create( {
            {static_cast<float>(x), static_cast<float>(coord)},0,
            ElementType::BLOCK, AdditionalFunc::getRandom(_missed_blocks_num),
            _building_data.scale}));
        coord += _building_data.delta.y;
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

BoundaryCreator::BoundaryCreator(const LocationBuildingData &building_data, QuadtreeEl &quadtree,
            ElementCreator &element_creator, LocationCreator &location_creator) :
        _building_data(building_data), _quadtree(&quadtree), _element_creator(&element_creator),
        _location_creator(&location_creator),
        _door_size(GeomAuxiliaryFunc::multiplyVectors(building_data.door_size_count, building_data.delta)){ }

Location *BoundaryCreator::createLocation(const sf::Vector2i &p0, const sf::Vector2i &p1,
        const DoorOpeningMask door_opening, const RoomType room_type) {
    const int start_x = p0.x + _building_data.delta.x;
    const int start_y = p0.y + _building_data.delta.y;
    const int last_x = p1.x - _building_data.delta.x;
    const int last_y = p1.y - _building_data.delta.y;

    const auto location = _location_creator->create({
        static_cast<float>(start_x),
        static_cast<float>(start_y),
        static_cast<float>(last_x),
        static_cast<float>(last_y)
    }, room_type);

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
        const DoorOpeningMask door_opening, const RoomType room_type) {
    const sf::Vector2i p1(p0.x + _building_data.delta.x * count_x, p0.y + _building_data.delta.y * count_y);
    return createLocation(p0, p1, door_opening, room_type);
}

int BoundaryCreator::createVertTransition(const sf::Vector2i &p0, const int last_y) const {
    const int last_x = p0.x + _door_size.x + _building_data.delta.x;
    
    createVertBoundary(p0.y, last_y, p0.x);
    createVertBoundary(p0.y, last_y, last_x);
    return last_x + _building_data.delta.x;
}

int BoundaryCreator::createHorTransition(const sf::Vector2i &p0, const int last_x) const {
    const int last_y = p0.y + _door_size.y + _building_data.delta.y;
    
    createHorBoundary(p0.x, last_x, p0.y);
    createHorBoundary(p0.x, last_x, last_y);
    return last_y + _building_data.delta.y;
}

const sf::Vector2i &BoundaryCreator::getDelta() const { return _building_data.delta; }

const sf::Vector2i &BoundaryCreator::getDoorSizeCount() const { return _building_data.door_size_count; }