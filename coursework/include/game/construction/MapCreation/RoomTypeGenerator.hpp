#pragma once
#include <random>

#include "../RoomType.hpp"

class RoomTypeGenerator final {
    mutable std::uniform_int_distribution<size_t> _random_type{1, 100};
    bool _is_created_portal = false;
    RoomType getAvailableRandomType() const;
public:
    RoomType generate(const bool generate_new_portal);
    [[nodiscard]] bool isCreatedPortal() const;
    explicit RoomTypeGenerator() = default;
    ~RoomTypeGenerator() noexcept = default;
    RoomTypeGenerator(RoomTypeGenerator&&) noexcept = delete;
    RoomTypeGenerator& operator=(RoomTypeGenerator&&) noexcept = delete;
    RoomTypeGenerator(const RoomTypeGenerator&) noexcept = delete;
    RoomTypeGenerator& operator=(const RoomTypeGenerator&) noexcept = delete;
};
