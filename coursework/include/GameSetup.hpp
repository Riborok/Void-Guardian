#pragma once
#include "GameContext.hpp"
#include "gui/GUIManager/GUIManager.hpp"
#include "initialization/DataInitialization.hpp"

struct GameSetup final {
    GameContext game_context;
    GUIManager gui_managers;
    GameSetup(): game_context(DataInitialization::initializeWindowInfo()),
        gui_managers(DataInitialization::initializeGUIManagers(game_context)){}
};