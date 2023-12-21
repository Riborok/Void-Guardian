#pragma once
#include "bullet/BulletMap.hpp"
#include "enemy/EnemyMap.hpp"
#include "player/PlayerMap.hpp"

struct EntityMaps {
    PlayerMap player_map;
    BulletMap bullet_map;
    EnemyMap enemy_map;
    EntityMaps() = default;
};