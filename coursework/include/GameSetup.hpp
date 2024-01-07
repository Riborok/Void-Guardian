#pragma once
#include "GameContext.hpp"
#include "gui/LoadingScreen.hpp"
#include "gui/SettingsManager.hpp"
#include "initialization/DataInitialization.hpp"

struct GameSetup final {
    GameContext game_context;
    LoadingScreen loading_screen;
    SettingsManager settings_manager;
    GameSetup(): game_context(DataInitialization::initializeWindowInfo()),
        loading_screen(game_context.window, game_context.fullscreen_toggler,
            DataInitialization::initializeLoadingScreenInfo(), DataInitialization::initializeColors()),
        settings_manager(game_context, DataInitialization::initializeSettingsManagerInfo(),
            DataInitialization::initializeSettingColors()){}
};