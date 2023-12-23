#pragma once
#include "bullet/BulletMap.hpp"
#include "enemy/EnemyMap.hpp"
#include "player/PlayerHolder.hpp"

struct FightingMaps {
    PlayerHolder player_holder;
    EnemyMap enemy_map;
    explicit FightingMaps(Player *player): player_holder(player) {}
};

struct EntityMaps {
    FightingMaps fighting_maps;
    BulletMap bullet_map;
    explicit EntityMaps(Player *player): fighting_maps(player) {}
};