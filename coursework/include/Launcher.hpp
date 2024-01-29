#pragma once
#include "GameSetup.hpp"
#include "files/FileOperator.hpp"
#include "game/GameStarter.hpp"
#include "gui/MenuController/MenuController.hpp"

class Launcher final {
    GameSetup *_game_setup;
    FileOperator _file_operator;
    MenuController _menu_controller;
    GameStarter _game_starter;
public:
    explicit Launcher(GameSetup &game_setup);
    void start();
    
    ~Launcher() noexcept = default;
    Launcher(Launcher&&) noexcept = delete;
    Launcher& operator=(Launcher&&) noexcept = delete;
    Launcher(const Launcher&) noexcept = delete;
    Launcher& operator=(const Launcher&) noexcept = delete;
};
