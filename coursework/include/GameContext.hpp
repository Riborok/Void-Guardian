#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

#include "files/PlayerProgress.hpp"
#include "game/entity/player/Control.hpp"
#include "game/input/FullscreenToggler.hpp"

struct GameContext final {
    sf::RenderWindow window;
    PlayerProgress player_progress;
    Control control;
    FullscreenToggler fullscreen_toggler;
    explicit GameContext(WindowInfo&& window_info): player_progress(), control(),
        fullscreen_toggler(window, std::move(window_info), false) { }
};