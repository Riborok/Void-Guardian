#pragma once
#include <SFML/System/Clock.hpp>

struct GameLoopState {
    sf::Clock clock;
    bool is_active = true;

    void changeActivity() {
        clock.restart();
        is_active = !is_active;
    }
};
