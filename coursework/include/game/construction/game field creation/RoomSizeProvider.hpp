#pragma once
#include <SFML/System/Vector2.hpp>

#include "RandomSize.hpp"
#include "../RoomType.hpp"

class RoomSizeProvider final {
    static constexpr int MAX_SIZE_OFFSET = 10;
    mutable RandomSize _arena_random_size;
    sf::Vector2i _max_size;
    static int makeEven(const int value);
public:
    explicit RoomSizeProvider(const size_t lvl);
    [[nodiscard]] sf::Vector2i getSize(const RoomType type) const noexcept(false);
    [[nodiscard]] const sf::Vector2i &getMaxSize() const;

    ~RoomSizeProvider() noexcept = default;
    RoomSizeProvider(RoomSizeProvider&&) noexcept = delete;
    RoomSizeProvider& operator=(RoomSizeProvider&&) noexcept = delete;
    RoomSizeProvider(const RoomSizeProvider&) noexcept = delete;
    RoomSizeProvider& operator=(const RoomSizeProvider&) noexcept = delete;
};
