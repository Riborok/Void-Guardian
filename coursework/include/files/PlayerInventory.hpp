#pragma once

struct PlayerInventory final {
    size_t character_num;
    size_t gun_num;
    PlayerInventory(const size_t character_num, const size_t gun_num): character_num(character_num), gun_num(gun_num) {}
    PlayerInventory() = default;
};