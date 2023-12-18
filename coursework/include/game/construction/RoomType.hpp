#pragma once

enum class RoomType final : size_t{
    SPAWN = 0,
    PORTAL,
    BOX,
    ARENA
};

constexpr size_t ROOM_TYPES_COUNT = static_cast<size_t>(RoomType::ARENA) + 1;