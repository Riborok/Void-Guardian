#include "../../include/game/GameSystemCreator.hpp"

GameSystem GameSystemCreator::create(const BuildingData &building_data, const sf::Vector2i &latest_map_index,
        const InOutPortals &portals, SimpleCreators &simple_creators, const EntityCreator &entity_creator, 
        CollisionTable &&type_collision) {
    const GameFieldCreator game_field_creator(latest_map_index);
    
    GameSystem result(game_field_creator.initialize(building_data.boundary_data), std::move(type_collision), entity_creator);
    game_field_creator.create(result.game_field, building_data, result.gun_manager, simple_creators, portals);
    
    return result;
}