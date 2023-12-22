#include "../../../include/game/construction/BoundaryCreator.hpp"

#include "../../../include/additionally/RandomGenerator.hpp"
#include "../../../include/game/construction/LocationCreator.hpp"
#include "../../../include/geometry/GeomAuxiliaryFunc.hpp"

void BoundaryCreator::createBlock(const sf::Vector2f &pos) const {
    _quadtree->insert(_simple_creators->element_creator.create({
        pos, 0, ElementType::BLOCK, _building_info.num, _building_info.boundary_data.scale}));
}

void BoundaryCreator::createMissedBlock(const int x, const int y, Location* location) const {
    location->addMissedBlock(_simple_creators->element_creator.create({
        {static_cast<float>(x), static_cast<float>(y)},
        0, ElementType::BLOCK, RandomGenerator::getRandom(_missed_blocks_num),
        _building_info.boundary_data.scale}));
}

void BoundaryCreator::createHorBoundary(int start_x, const int last_x, const int y) const {
    while (start_x < last_x) {
        createBlock({static_cast<float>(start_x), static_cast<float>(y)});
        start_x += _building_info.boundary_data.delta.x;
    }
}

void BoundaryCreator::createHorMissedBlocks(int start_x, const int last_x, const int y, Location *location) const {
    while (start_x < last_x) {
        createMissedBlock(start_x, y, location);
        start_x += _building_info.boundary_data.delta.x;
    }
}

void BoundaryCreator::createVertBoundary(int start_y, const int last_y, const int x) const {
    while (start_y < last_y) {
        createBlock({static_cast<float>(x), static_cast<float>(start_y)});
        start_y += _building_info.boundary_data.delta.y;
    }
}

void BoundaryCreator::createVertMissedBlocks(int start_y, const int last_y, const int x, Location *location) const {
    while (start_y < last_y) {
        createMissedBlock(x, start_y, location);
        start_y += _building_info.boundary_data.delta.y;
    }
}

void BoundaryCreator::createHorBoundaryWithDoor(const sf::Vector2i &p, const int last, Location *location, const int door_size) const {
    const int last_offset = (p.x + last - door_size) / 2;
    createHorBoundary(p.x, last_offset, p.y);
    createHorMissedBlocks(last_offset, last_offset + door_size, p.y, location);
    createHorBoundary(last_offset + door_size, last, p.y);
}

void BoundaryCreator::createVertBoundaryWithDoor(const sf::Vector2i &p, const int last, Location *location, const int door_size) const {
    const int last_offset = (p.y + last - door_size) / 2;
    createVertBoundary(p.y, last_offset, p.x);
    createVertMissedBlocks(last_offset, last_offset + door_size, p.x, location);
    createVertBoundary(last_offset + door_size, last, p.x);
}

BoundaryCreator::BoundaryCreator(const BoundaryInfo &building_info, QuadtreeEl &quadtree, SimpleCreators &simple_creators) :
        _building_info(building_info), _quadtree(&quadtree), _simple_creators(&simple_creators),
        _door_size(GeomAuxiliaryFunc::multiplyVectors(building_info.boundary_data.door_size_count,
            building_info.boundary_data.delta)){ }

Location *BoundaryCreator::createLocation(const sf::Vector2i &p0, const sf::Vector2i &p1,
                                          const DoorOpeningMask door_opening, const RoomType room_type) const {
    const int start_x = p0.x + _building_info.boundary_data.delta.x;
    const int start_y = p0.y + _building_info.boundary_data.delta.y;
    const int last_x = p1.x - _building_info.boundary_data.delta.x;
    const int last_y = p1.y - _building_info.boundary_data.delta.y;

    const auto location = _simple_creators->location_creator.create({
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

    if (hasBottomDoor(door_opening)) createHorBoundaryWithDoor({p0.x, last_y}, p1.x, location, _door_size.x);
    else                             createHorBoundary(p0.x, p1.x, last_y);
    
    return location;
}

Location *BoundaryCreator::createLocation(const sf::Vector2i &p0, const int count_x, const int count_y,
        const DoorOpeningMask door_opening, const RoomType room_type) const {
    const sf::Vector2i p1(p0.x + _building_info.boundary_data.delta.x * count_x,
        p0.y + _building_info.boundary_data.delta.y * count_y);
    return createLocation(p0, p1, door_opening, room_type);
}

int BoundaryCreator::createVertTransition(const sf::Vector2i &p0, const int last_y) const {
    const int last_x = p0.x + _door_size.x + _building_info.boundary_data.delta.x;
    
    createVertBoundary(p0.y, last_y, p0.x);
    createVertBoundary(p0.y, last_y, last_x);
    return last_x + _building_info.boundary_data.delta.x;
}

int BoundaryCreator::createHorTransition(const sf::Vector2i &p0, const int last_x) const {
    const int last_y = p0.y + _door_size.y + _building_info.boundary_data.delta.y;
    
    createHorBoundary(p0.x, last_x, p0.y);
    createHorBoundary(p0.x, last_x, last_y);
    return last_y + _building_info.boundary_data.delta.y;
}

const sf::Vector2i &BoundaryCreator::getDelta() const { return _building_info.boundary_data.delta; }

const sf::Vector2i &BoundaryCreator::getDoorSizeCount() const { return _building_info.boundary_data.door_size_count; }