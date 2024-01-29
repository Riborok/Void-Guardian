#pragma once
#include "../geometry/collision/CollisionTable.hpp"
#include "../sprite/SpriteInfos.hpp"
#include "construction/BuildingParameters.hpp"
#include "construction/game field creation/portal/PortalInfo.hpp"
#include "entity/InfoTables.hpp"

struct GameInfo final {
    SimpleSpriteInfos simple_sprite_sprite_infos;
    AnimatedSpriteInfos animated_sprite_infos;
    CollisionTable collision_table;
    
    BuildingParameters building_parameters;
    InOutPortalInfo in_out_portal_info;
    
    EntityInfoTables entity_info_tables;

    std::string health_font_src;
    
    GameInfo(SimpleSpriteInfos &&simple_sprite_sprite_infos,
            AnimatedSpriteInfos &&animated_sprite_infos,
            CollisionTable &&collision_table,
            BuildingParameters &&building_parameters,
            InOutPortalInfo &&in_out_portal_info,
            EntityInfoTables &&entity_info_tables,
            std::string &&health_font_src):
        simple_sprite_sprite_infos(simple_sprite_sprite_infos),
        animated_sprite_infos(animated_sprite_infos),
        collision_table(std::move(collision_table)),
        building_parameters(building_parameters),
        in_out_portal_info(in_out_portal_info),
        entity_info_tables(entity_info_tables),
        health_font_src(std::move(health_font_src)){}
};