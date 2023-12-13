#pragma once
#include <random>
#include <SFML/System/Vector2.hpp>

#include "../RoomType.hpp"

class RoomSizeManager final {
    sf::Vector2i _max_size;

    mutable std::uniform_int_distribution<int> _random_size_x{18, 24};
    mutable std::uniform_int_distribution<int> _random_size_y{14, 18};
    static int makeEven(const int value);
public:
    explicit RoomSizeManager(const sf::Vector2i &max_size = { 36, 26 });
    sf::Vector2i getSize(const RoomType type) const noexcept(false);
    [[nodiscard]] const sf::Vector2i &getMaxSize() const;

    ~RoomSizeManager() noexcept = default;
    RoomSizeManager(RoomSizeManager&&) noexcept = delete;
    RoomSizeManager& operator=(RoomSizeManager&&) noexcept = delete;
    RoomSizeManager(const RoomSizeManager&) noexcept = delete;
    RoomSizeManager& operator=(const RoomSizeManager&) noexcept = delete;
};
