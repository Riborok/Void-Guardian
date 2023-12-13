#pragma once

struct PlayerInventory final {
    int wraith_num;
    int gun_num;
    PlayerInventory(const int wraith_num, const int gun_num): wraith_num(wraith_num), gun_num(gun_num) {}
    PlayerInventory() = default;
};