#pragma once
#include <random>

#include "RoomType.hpp"
#include "../../../additionally/AdditionalFunc.hpp"

class RoomTypeGenerator final {
    std::uniform_int_distribution<size_t> _random_type{1, 100};
    bool _is_created_portal = false;
    RoomType getAvailableRandomType() {
        return AdditionalFunc::getRandom(_random_type) >= 80 ? RoomType::BOX : RoomType::BATTLE;
    }
public:
    explicit RoomTypeGenerator() = default;
    RoomType generate(const bool generate_new_portal) {
        if (_is_created_portal || !generate_new_portal) {
            return getAvailableRandomType();
        }
        else {
            _is_created_portal = true;
            return RoomType::PORTAL;
        }
    }
    [[nodiscard]] bool isCreatedPortal() const { return _is_created_portal; }
    ~RoomTypeGenerator() noexcept = default;
    RoomTypeGenerator(RoomTypeGenerator&&) noexcept = delete;
    RoomTypeGenerator& operator=(RoomTypeGenerator&&) noexcept = delete;
    RoomTypeGenerator(const RoomTypeGenerator&) noexcept = delete;
    RoomTypeGenerator& operator=(const RoomTypeGenerator&) noexcept = delete;
};
