#pragma once
#include "GameContext.hpp"
#include "gui/UIController/UIController.hpp"
#include "initialization\InfoInitialization.hpp"

struct GameSetup final {
    GameContext game_context;
    UIController ui_controller;
    GameSetup(): game_context(InfoInitialization::initializeWindowInfo()),
        ui_controller(InfoInitialization::initializeUIController(game_context)){}
};