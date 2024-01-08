#pragma once
#include "../game/CharacterLimits.hpp"
#include "../game/GameData.hpp"
#include "../game/input/WindowInfo.hpp"
#include "../gui/Colors.hpp"
#include "../gui/GUIManager/GUIManager.hpp"

namespace DataInitialization {
    GameData initializeGameData();
    WindowInfo initializeWindowInfo();
    std::string initializeAimCursorSrc();
    
    GUIManager initializeGUIManagers(GameContext &game_context);
    Colors initializeColors();
    std::string initializeAboutUrl();

    CharacterLimits initializeCharacterLimits();
}