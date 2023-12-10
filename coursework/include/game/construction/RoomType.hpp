#pragma once

enum class RoomType final : size_t{
    SPAWN = 0,
    PORTAL,
    BOX,
    BATTLE
};

constexpr size_t ROOM_TYPES_COUNT = static_cast<size_t>(RoomType::BATTLE) + 1;