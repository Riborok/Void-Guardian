#pragma once
#include "bullet/BulletMap.hpp"
#include "enemy/EnemyMap.hpp"
#include "player/PlayerHolder.hpp"

struct EntityMaps {
    PlayerHolder player_holder;
    EnemyMap enemy_map;
    BulletMap bullet_map;
    explicit EntityMaps(Player *player): player_holder(player) {}
};