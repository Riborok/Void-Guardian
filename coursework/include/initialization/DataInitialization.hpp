#pragma once
#include "../game/GameData.hpp"
#include "../game/input/WindowInfo.hpp"
#include "../gui/Colors.hpp"
#include "../gui/LoadingScreenInfo.hpp"
#include "../gui/MenuManagerInfo.hpp"
#include "../gui/SettingsManagerInfo.hpp"

namespace DataInitialization {
    GameData initializeGameData();
    WindowInfo initializeWindowInfo();
    std::string initializeAimCursorSrc();
    
    MenuManagerInfo initializeMenuManagerInfo(const std::string &title);
    LoadingScreenInfo initializeLoadingScreenInfo();
    SettingsManagerInfo initializeSettingsManagerInfo();
    
    Colors initializeColors();
    MenuColors initializeMenuColors();
    SettingColors initializeSettingColors();
}