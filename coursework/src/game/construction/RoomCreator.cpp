#include "../../../include/game/construction/RoomCreator.hpp"

#include "../../../include/additionally/AdditionalFunc.hpp"
#include "../../../include/game/construction/BoundaryCreator.hpp"
#include "../../../include/game/construction/LocationCreation.hpp"

RoomCreator::RoomCreator(QuadtreeEl &quadtree, const int block_num, const int background_num,
    const sf::Vector2i &door_size_count, const sf::Vector2f &block_scale, const sf::Vector2f &background_scale):
        _door_size_count(door_size_count),
        _scale_factor(block_scale.x / background_scale.x, block_scale.y / background_scale.y),
        _boundary_creation(block_num, block_scale, door_size_count, quadtree),
        _background_creator(background_num, background_scale, quadtree) { }

int RoomCreator::getBackgroundCountX(const int count_x) const {
    return static_cast<int>(_scale_factor.x * static_cast<float>(count_x));
}

int RoomCreator::getBackgroundCountY(const int count_y) const {
    return static_cast<int>(_scale_factor.y * static_cast<float>(count_y));
}

Location *RoomCreator::create(const sf::Vector2i &p0, const sf::Vector2i &p1,
    const DoorOpeningMask door_opening) {
    _background_creator.createBackground(p0, p1);
    return _boundary_creation.createLocation(p0, p1, door_opening);
}

Location *RoomCreator::create(const sf::Vector2i &p0, const int count_x, const int count_y,
    const DoorOpeningMask door_opening) {
    _background_creator.createBackground(p0, getBackgroundCountX(count_x), getBackgroundCountY(count_y));
    return _boundary_creation.createLocation(p0, count_x, count_y, door_opening);
}

void RoomCreator::createVertTransition(sf::Vector2i p0, const int last_y) const {
    p0.x -= _boundary_creation.getDelta().x;
    const int last_x = _boundary_creation.createVertTransition(p0, last_y);
    _background_creator.createBackground(p0, {last_x, last_y});
}
    
void RoomCreator::createHorTransition(sf::Vector2i p0, const int last_x) const {
    p0.y -= _boundary_creation.getDelta().y; 
    const int last_y = _boundary_creation.createHorTransition(p0, last_x);
    _background_creator.createBackground(p0, {last_x, last_y});
}

const sf::Vector2i &RoomCreator::getBlockDelta() const { return _boundary_creation.getDelta(); }
const sf::Vector2i &RoomCreator::getDoorSizeCount() const { return _door_size_count; }