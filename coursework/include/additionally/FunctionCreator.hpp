#pragma once
#include <functional>

#include "../game/PauseSubset.hpp"
#include "../game/WindowParam.hpp"
#include "../gui/GUIManager/PauseManager.hpp"

typedef std::function<void()> SetNewWindowSize;
typedef std::function<void()> SetPause;
typedef std::function<void()> ToggleFullscreen;

namespace FunctionCreator {
    inline SetNewWindowSize createSetNewWindowSize(WindowParam &window_param, sf::RenderWindow &window) {
        return [&window_param, &window]{window_param.updateSize(static_cast<sf::Vector2f>(window.getSize()));};
    }
    inline SetPause createSetPause(PauseSubset &pause_subset, GameState &game_state, sf::Clock &clock,
        sf::RenderWindow &window) {
        return [&pause_subset, &game_state, &clock, &window] {
            pause_subset.pause_manager->startPauseMenu(game_state);
            clock.restart();
            window.setMouseCursor(pause_subset.cursor);
        };
    }
    inline ToggleFullscreen createToggleFullscreen(FullscreenToggler &fullscreen_toggler,
        const sf::Cursor &cursor, SetNewWindowSize &set_new_window_size) {
        return [&fullscreen_toggler, &cursor, &set_new_window_size] {
            fullscreen_toggler.toggleFullscreen(cursor);
            set_new_window_size();
        };
    }
}