#pragma once
#include "../game/CharacterLimits.hpp"
#include "../game/GameInfo.hpp"
#include "../game/input/WindowInfo.hpp"
#include "../gui/Colors.hpp"
#include "../gui/UIController/UIController.hpp"

namespace InfoInitialization {
    GameInfo initializeGameInfo();
    WindowInfo initializeWindowInfo();
    std::string initializeAimCursorSrc();
    
    UIController initializeUIController(GameContext &game_context);
    Colors initializeColors();
    std::string initializeAboutUrl();

    CharacterLimits initializeCharacterLimits();
}