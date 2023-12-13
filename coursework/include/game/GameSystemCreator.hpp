#pragma once
#include "GameSystem.hpp"

namespace GameSystemCreator {
    GameSystem create(const BuildingData &building_data, const sf::Vector2i &latest_map_index,
        const InOutPortals &portals, SimpleCreators &simple_creators, const EntityCreator &entity_creator,
        CollisionTable &&type_collision);
}