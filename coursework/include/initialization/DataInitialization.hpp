﻿#pragma once
#include "../game/GameData.hpp"
#include "../game/input/WindowInfo.hpp"
#include "../gui/Colors.hpp"
#include "../gui/LoadingScreenInfo.hpp"
#include "../gui/MenuManagerInfo.hpp"

namespace DataInitialization {
    GameData initializeGameData();
    WindowInfo initializeWindowInfo();
    MenuManagerInfo initializeMenuManagerInfo(const std::string &title);
    std::string initializeAimCursorSrc();
    LoadingScreenInfo initializeLoadingScreenInfo();
    Colors initializeColors();
    MenuColors initializeMenuColors();
}