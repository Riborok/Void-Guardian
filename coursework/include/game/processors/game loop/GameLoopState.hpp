#pragma once
#include <SFML/System/Clock.hpp>

struct GameLoopState final {
    sf::Clock clock;
    bool is_active = true;
    explicit GameLoopState(const sf::Clock clock);
    GameLoopState() = default;

    void changeActivity();
};