// ReSharper disable CppClangTidyPerformanceMoveConstArg
#pragma once
#include "../geometry/collision/CollisionTable.hpp"
#include "../sprite/Infos.hpp"
#include "construction/BuildingData.hpp"
#include "construction/game field creation/portal/PortalData.hpp"
#include "entity/InfoTables.hpp"
#include "input/WindowInfo.hpp"

struct GameData final {
    SimpleSpriteInfos simple_sprite_infos;
    AnimatedSpriteInfos animated_sprite_infos;
    CollisionTable collision_table;
    
    BuildingData building_data;
    InOutPortals portals_data;
    
    WindowInfo window_info;
    
    WraithInfos wraith_infos;
    GunInfos gun_infos;
    BulletInfos bullet_infos;
    
    GameData(SimpleSpriteInfos &&simple_sprite_infos,
            AnimatedSpriteInfos &&animated_sprite_infos,
            CollisionTable &&collision_table,
            BuildingData &&building_data,
            InOutPortals &&portals_data,
            WindowInfo &&window_info,
            WraithInfos &&wraith_infos,
            GunInfos &&gun_infos,
            BulletInfos &&bullet_infos):
        simple_sprite_infos(std::move(simple_sprite_infos)),
        animated_sprite_infos(std::move(animated_sprite_infos)),
        collision_table(std::move(collision_table)),
        building_data(std::move(building_data)),
        portals_data(std::move(portals_data)),
        window_info(std::move(window_info)),
        wraith_infos(std::move(wraith_infos)),
        gun_infos(std::move(gun_infos)),
        bullet_infos(std::move(bullet_infos)) {}
};