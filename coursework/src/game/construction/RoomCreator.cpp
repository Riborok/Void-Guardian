#include "../../../include/game/construction/RoomCreator.hpp"

#include "../../../include/game/construction/BoundaryCreator.hpp"
#include "../../../include/game/construction/LocationCreator.hpp"

sf::Vector2f getScaleFactor(const sf::Vector2f &block_scale, const sf::Vector2f &background_scale) {
    return {block_scale.x / background_scale.x, block_scale.y / background_scale.y};
}

RoomCreator::RoomCreator(QuadtreeEl &quadtree, const BuildingData &building_data, SimpleCreators &simple_creators):
        _scale_factor(getScaleFactor(building_data.boundary_data.scale, building_data.background_data.scale)),
        _boundary_creator(building_data.boundary_data, quadtree, simple_creators),
        _background_creator(building_data.background_data, quadtree, simple_creators.element_creator) { }

int RoomCreator::getBackgroundCountX(const int count_x) const {
    return static_cast<int>(_scale_factor.x * static_cast<float>(count_x));
}

int RoomCreator::getBackgroundCountY(const int count_y) const {
    return static_cast<int>(_scale_factor.y * static_cast<float>(count_y));
}

Location *RoomCreator::create(const sf::Vector2i &p0, const sf::Vector2i &p1,
    const DoorOpeningMask door_opening, const RoomType room_type) {
    _background_creator.createBackground(p0, p1);
    return _boundary_creator.createLocation(p0, p1, door_opening, room_type);
}

Location *RoomCreator::create(const sf::Vector2i &p0, const int count_x, const int count_y,
    const DoorOpeningMask door_opening, const RoomType room_type) {
    _background_creator.createBackground(p0, getBackgroundCountX(count_x), getBackgroundCountY(count_y));
    return _boundary_creator.createLocation(p0, count_x, count_y, door_opening, room_type);
}

void RoomCreator::createVertTransition(sf::Vector2i p0, const int last_y) const {
    p0.x -= _boundary_creator.getDelta().x;
    const int last_x = _boundary_creator.createVertTransition(p0, last_y);
    _background_creator.createBackground(p0, {last_x, last_y});
}
    
void RoomCreator::createHorTransition(sf::Vector2i p0, const int last_x) const {
    p0.y -= _boundary_creator.getDelta().y; 
    const int last_y = _boundary_creator.createHorTransition(p0, last_x);
    _background_creator.createBackground(p0, {last_x, last_y});
}

const sf::Vector2i &RoomCreator::getBlockDelta() const { return _boundary_creator.getDelta(); }
const sf::Vector2i &RoomCreator::getDoorSizeCount() const { return _boundary_creator.getDoorSizeCount(); }