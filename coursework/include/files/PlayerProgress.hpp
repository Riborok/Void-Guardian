#pragma once
#include "PlayerInventory.hpp"

struct PlayerProgress final {
    PlayerInventory player_inventory;
    size_t lvl;
    PlayerProgress(const PlayerInventory &player_inventory, const size_t lvl):
        player_inventory(player_inventory), lvl(lvl) {}
    PlayerProgress() = default;
};