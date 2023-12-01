#pragma once
#include "bullet/BulletMap.hpp"
#include "player/PlayerMap.hpp"

struct EntityMaps {
    PlayerMap player_map;
    BulletMap bullet_map;
    EntityMaps() = default;
};
