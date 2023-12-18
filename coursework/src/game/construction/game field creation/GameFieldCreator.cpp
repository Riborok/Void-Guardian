#include "../../../../include/game/construction/game field creation/GameFieldCreator.hpp"

#include "../../../../include/additionally/RandomGenerator.hpp"
#include "../../../../include/additionally/SimpleCreators.hpp"
#include "../../../../include/game/construction/game field creation/LocationPlaceholder.hpp"
#include "../../../../include/game/construction/game field creation/RoomSizeManager.hpp"

RoomType GameFieldCreator::generateType() {
    const auto &item_sequence = _location_info_map.getItemSequence();
    return _room_type_generator.generate(item_sequence.size() > _min_quantity);
}

LocationInfo* GameFieldCreator::createLocationInfo(const sf::Vector2i& next_pos, const RoomType room_type) {
    auto* next_location = new LocationInfo(next_pos, _room_size_manager.getSize(room_type), room_type);
    _location_info_map.set(next_location, next_location->getPosition());
    return next_location;
}

void GameFieldCreator::createTransitions(LocationInfo &location_info, const DoorOpeningMask mask) {
    LocationInfo* connected_locations[TOTAL_DIRECTIONS];
    size_t count = 0;
    for (const DoorOpening door_opening : DOOR_OPENINGS) {
        if (hasDoor(mask, door_opening)) {
            const auto new_pos(movePosition(door_opening, location_info.getPosition()));
            if (auto *neighbour = _location_info_map.getArray2D().get(new_pos); neighbour)
                location_info.addOutgoingDoor(neighbour, door_opening);
            else {
                const auto type = generateType();
                auto* next_location = createLocationInfo(new_pos, type);
                location_info.addOutgoingDoor(next_location, door_opening);
                if (type != RoomType::PORTAL)
                    connected_locations[count++] = next_location;
            }
        }
    }
    for (size_t i = 0; i < count; ++i)
        createNeighbors(connected_locations[i]);
}

sf::Vector2i GameFieldCreator::getLatestMapIndex() const {
    const size_t even = _lvl & ~1u;
    const size_t is_odd = _lvl & 1u;
    return {static_cast<int>(START_INDEX + even), static_cast<int>(START_INDEX + even + is_odd)};
}

size_t GameFieldCreator::checkCoordinate(DoorOpeningMask &mask, const sf::Vector2i &pos,
        const int coord, const int critical_index, const DoorOpening door_opening) const {
    if (coord == critical_index) {
        mask &= ~doorToMask(door_opening);
        return 1;
    }
    
    const auto *neighbor = _location_info_map.getArray2D().get(movePosition(door_opening, pos));
    if (!neighbor)
        return 0;
    
    if (const auto type = neighbor->getRoomType(); type == RoomType::SPAWN || type == RoomType::PORTAL)
        mask &= ~doorToMask(door_opening);
    
    return 1;
}

size_t GameFieldCreator::getTotalObstacles(DoorOpeningMask &mask, const sf::Vector2i &pos) const {
    return checkCoordinate(mask, pos, pos.x, 0, DoorOpening::LEFT)
     + checkCoordinate(mask, pos, pos.x, _location_info_map.getArray2D().getLastIndex().x, DoorOpening::RIGHT)
     + checkCoordinate(mask, pos, pos.y, 0, DoorOpening::TOP)
     + checkCoordinate(mask, pos, pos.y, _location_info_map.getArray2D().getLastIndex().y, DoorOpening::BOTTOM);
}

DoorOpeningMask GameFieldCreator::getDirections(const sf::Vector2i &pos) const {
    DoorOpeningMask opening_mask = ALL_DIRECTIONS_MASK;
    
    const size_t total_obstacles = getTotalObstacles(opening_mask, pos);
    const size_t strikeout_count = total_obstacles == TOTAL_DIRECTIONS
        ? TOTAL_DIRECTIONS / 2 // There is a chance to open an additional door (between the current and existing one)
        : TOTAL_DIRECTIONS - total_obstacles + (_room_type_generator.isCreatedPortal() ? 1 : -1);
    
    for (size_t i = strikeout_count; i > 0; --i)
        opening_mask &= ~doorToMask(_direction_generator.generateDirection());
    return opening_mask;
}

void GameFieldCreator::createNeighbors(LocationInfo* location_info) {
    const DoorOpeningMask door_opening_mask = getDirections(location_info->getPosition());
    if (door_opening_mask != 0) { createTransitions(*location_info, door_opening_mask); }
}

void GameFieldCreator::initSpawnRoomPos(sf::Vector2i& pos, sf::Vector2i& next_pos,
        DoorOpening& neighbors_direction) const {
    std::uniform_int_distribution<int> zero_or_one{0, 1};
    if (RandomGenerator::getRandom(zero_or_one) == 0) {
        if (RandomGenerator::getRandom(zero_or_one) == 0) {
            pos.x = 0;
            next_pos.x = 1;
            neighbors_direction = DoorOpening::RIGHT;
        }
        else {
            pos.x = _location_info_map.getArray2D().getLastIndex().x;
            next_pos.x = _location_info_map.getArray2D().getLastIndex().x - 1;
            neighbors_direction = DoorOpening::LEFT;
        }
        std::uniform_int_distribution<int> range(0, _location_info_map.getArray2D().getLastIndex().y);
        pos.y = RandomGenerator::getRandom(range);
        next_pos.y = pos.y;
    }
    else {
        if (RandomGenerator::getRandom(zero_or_one) == 0) {
            pos.y = 0;
            next_pos.y = 1;
            neighbors_direction = DoorOpening::BOTTOM;
        }
        else {
            pos.y = _location_info_map.getArray2D().getLastIndex().y;
            next_pos.y = _location_info_map.getArray2D().getLastIndex().y - 1;
            neighbors_direction = DoorOpening::TOP;
        }
        std::uniform_int_distribution<int> range(0, _location_info_map.getArray2D().getLastIndex().x);
        pos.x = RandomGenerator::getRandom(range);
        next_pos.x = pos.x;
    }
}

void GameFieldCreator::createRooms() {
    sf::Vector2i pos;
    sf::Vector2i next_pos;
    DoorOpening neighbors_direction;

    initSpawnRoomPos(pos, next_pos, neighbors_direction);
    
    auto* spawn = createLocationInfo(pos, RoomType::SPAWN);
    auto* next_location = createLocationInfo(next_pos, RoomType::ARENA);
    spawn->addOutgoingDoor(next_location, neighbors_direction);
    createNeighbors(next_location);
    if (!_room_type_generator.isCreatedPortal()) { addExtraRooms(); }
}

void GameFieldCreator::addExtraRooms() {
    auto& item_sequence = _location_info_map.getItemSequence();
    do {
        for (size_t i = item_sequence.size(); i > 0; --i) {
            LocationInfo &location_info = *item_sequence[i - 1];
            
            DoorOpeningMask opening_mask = ALL_DIRECTIONS_MASK;
            const size_t total_obstacles = getTotalObstacles(opening_mask, location_info.getPosition());
            if (total_obstacles != TOTAL_DIRECTIONS) { 
                createTransitions(location_info, opening_mask);
                break;
            }
        }
    } while(!_room_type_generator.isCreatedPortal());
}

GameFieldCreator::GameFieldCreator(const size_t lvl) noexcept :
    _lvl(lvl),
    _location_info_map(getLatestMapIndex(), nullptr),
    _min_quantity(_location_info_map.getArray2D().getTotalCount() * 2 / 3) { createRooms(); }

[[nodiscard]] sf::Vector2f GameFieldCreator::getStartPoint(const sf::Vector2i &block_delta) const {
    const auto [p0, p1] = _location_info_map.getItemSequence()[0]->getRangeRect(block_delta,
        _room_size_manager.getMaxSize());
    return {static_cast<float>((p0.x + p1.x)) / 2.0f, static_cast<float>((p0.y + p1.y)) / 2.0f};
}

GameField GameFieldCreator::initialize(const BoundaryData &boundary_data) const {
    return {
        LocationTransformation::getMinMaxPoint(_location_info_map.getItemSequence(),
            _room_size_manager.getMaxSize(), boundary_data.delta),
        getStartPoint(boundary_data.delta)
    };
}

void GameFieldCreator::create(GameField& game_field, const BuildingData &building_data, GunManager &gun_manager,
        SimpleCreators &simple_creators, const InOutPortals& portals_data) const {
    const RoomCreator room_creator(game_field.quadtree_el, building_data, simple_creators);
    LocationMap location_map(_location_info_map.getArray2D().getLastIndex(), nullptr);
    
    LocationTransformation::buildLocation(_location_info_map.getItemSequence(), location_map,
        _room_size_manager.getMaxSize(), room_creator, game_field.quadtree_loc);
    LocationPlaceholder::fillRooms(location_map, gun_manager,
        {simple_creators.element_creator, game_field, portals_data},
        {room_creator.getBoundaryCreator(), {game_field.spawn_map}}, _lvl);
}

GameFieldCreator::~GameFieldCreator() noexcept {
    for (const auto *el : _location_info_map.getItemSequence())
        delete el;
}