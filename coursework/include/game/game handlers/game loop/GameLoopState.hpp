#pragma once
#include <SFML/System/Clock.hpp>

struct GameLoopState final {
    sf::Clock clock;
    bool is_active = true;
    GameLoopState() = default;
};