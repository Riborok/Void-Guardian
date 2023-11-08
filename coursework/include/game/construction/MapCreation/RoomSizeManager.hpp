#pragma once
#include <random>
#include <SFML/System/Vector2.hpp>

#include "MCAuxiliaryTools.hpp"

class RoomSizeManager final {
    sf::Vector2i _max_size;

    std::uniform_int_distribution<int> _random_size_x{16, 22};
    std::uniform_int_distribution<int> _random_size_y{10, 14};
    static int makeEven(const int value);
public:
    explicit RoomSizeManager(const sf::Vector2i &max_size = { 32, 22 });
    sf::Vector2i getSize(const RoomType type);
    [[nodiscard]] const sf::Vector2i &getMaxSize() const;

    ~RoomSizeManager() noexcept = default;
    RoomSizeManager(RoomSizeManager&&) noexcept = default;
    RoomSizeManager& operator=(RoomSizeManager&&) noexcept = default;
    RoomSizeManager(const RoomSizeManager&) noexcept = delete;
    RoomSizeManager& operator=(const RoomSizeManager&) noexcept = delete;
};
