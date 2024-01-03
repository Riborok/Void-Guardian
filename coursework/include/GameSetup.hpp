#pragma once
#include "GameContext.hpp"
#include "gui/LoadingScreen.hpp"
#include "initialization/DataInitialization.hpp"

struct GameSetup final {
    GameContext game_context;
    LoadingScreen loading_screen;
    GameSetup(): game_context(DataInitialization::initializeWindowInfo()),
        loading_screen(game_context.window, game_context.fullscreen_toggler,
            DataInitialization::initializeLoadingScreenInfo(), DataInitialization::initializeColors()) {}
};