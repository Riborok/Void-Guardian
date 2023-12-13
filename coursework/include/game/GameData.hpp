﻿// ReSharper disable CppClangTidyPerformanceMoveConstArg
#pragma once
#include <SFML/System/Vector2.hpp>

#include "../geometry/collision/CollisionTable.hpp"
#include "../sprite/Infos.hpp"
#include "construction/BuildingData.hpp"
#include "construction/MapCreation/PortalData.hpp"
#include "entity/InfoTables.hpp"

struct GameData final {
    SimpleSpriteInfos simple_sprite_infos;
    AnimatedSpriteInfos animated_sprite_infos;
    CollisionTable collision_table;
    
    BuildingData building_data;
    InOutPortals portals_data;
    sf::Vector2i latest_map_index;
    
    std::string title;
    std::string icon_src;
    
    WraithInfos wraith_infos;
    GunInfos gun_infos;
    BulletInfos bullet_infos;
    
    GameData(SimpleSpriteInfos &&simple_sprite_infos,
            AnimatedSpriteInfos &&animated_sprite_infos,
            CollisionTable &&collision_table,
            BuildingData &&building_data,
            InOutPortals &&portals_data,
            sf::Vector2i &&latest_map_index,
            std::string &&game_title,
            std::string &&game_icon_src,
            WraithInfos &&wraith_infos,
            GunInfos &&gun_infos,
            BulletInfos &&bullet_infos):
        simple_sprite_infos(std::move(simple_sprite_infos)),
        animated_sprite_infos(std::move(animated_sprite_infos)),
        collision_table(std::move(collision_table)),
        building_data(std::move(building_data)),
        portals_data(std::move(portals_data)),
        latest_map_index(std::move(latest_map_index)),
        title(std::move(game_title)),
        icon_src(std::move(game_icon_src)),
        wraith_infos(std::move(wraith_infos)),
        gun_infos(std::move(gun_infos)),
        bullet_infos(std::move(bullet_infos)) {}
};
