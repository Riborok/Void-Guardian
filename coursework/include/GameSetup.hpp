#pragma once
#include "GameContext.hpp"
#include "gui/GUIManager/GUIManager.hpp"
#include "initialization/DataInitialization.hpp"

struct GameSetup final {
    GameContext game_context;
    GUIManager gui_manager;
    GameSetup(): game_context(DataInitialization::initializeWindowInfo()),
        gui_manager(DataInitialization::initializeGUIManagers(game_context)){}
};