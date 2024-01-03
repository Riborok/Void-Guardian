#pragma once
#include "GameSetup.hpp"
#include "files/FileManager.hpp"
#include "game/GameManager.hpp"
#include "gui/MenuManager.hpp"

class Launcher final {
    GameSetup *_game_setup;
    FileManager _file_manager;
    MenuManager _menu_manager;
    GameManager _game_manager;
public:
    explicit Launcher(GameSetup &game_setup);
    void start();
    
    ~Launcher() noexcept = default;
    Launcher(Launcher&&) noexcept = delete;
    Launcher& operator=(Launcher&&) noexcept = delete;
    Launcher(const Launcher&) noexcept = delete;
    Launcher& operator=(const Launcher&) noexcept = delete;
};
