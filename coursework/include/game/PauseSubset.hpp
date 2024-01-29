#pragma once
#include "../gui/UIController/PauseController.hpp"

struct PauseSubset final {
    PauseController *pause_controller;
    sf::Cursor cursor;
    explicit PauseSubset(PauseController &pause_controller): pause_controller(&pause_controller) {}
};