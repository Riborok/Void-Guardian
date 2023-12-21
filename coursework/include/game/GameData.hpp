#pragma once
#include "../geometry/collision/CollisionTable.hpp"
#include "../sprite/Infos.hpp"
#include "construction/BuildingData.hpp"
#include "construction/game field creation/portal/PortalData.hpp"
#include "entity/InfoTables.hpp"

struct GameData final {
    SimpleSpriteInfos simple_sprite_infos;
    AnimatedSpriteInfos animated_sprite_infos;
    CollisionTable collision_table;
    
    BuildingData building_data;
    InOutPortals portals_data;
    
    EntityInfoTables entity_info_tables;
    GameData(SimpleSpriteInfos &&simple_sprite_infos,
            AnimatedSpriteInfos &&animated_sprite_infos,
            CollisionTable &&collision_table,
            BuildingData &&building_data,
            InOutPortals &&portals_data,
            EntityInfoTables &&entity_info_tables):
        simple_sprite_infos(simple_sprite_infos),
        animated_sprite_infos(animated_sprite_infos),
        collision_table(std::move(collision_table)),
        building_data(building_data),
        portals_data(portals_data),
        entity_info_tables(entity_info_tables){}
};