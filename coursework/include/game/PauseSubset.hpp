#pragma once
#include "../gui/GUIManager/PauseManager.hpp"

struct PauseSubset final {
    PauseManager *pause_manager;
    sf::Cursor cursor;
    explicit PauseSubset(PauseManager &pause_manager): pause_manager(&pause_manager) {}
};