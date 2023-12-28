#pragma once
#include "GameContext.hpp"
#include "files/FileManager.hpp"
#include "game/GameManager.hpp"
#include "gui/MenuManager.hpp"

// TODO: Make a normal launcher
class Launcher final {
    GameContext _game_context;
    FileManager _file_manager;
    GameManager _game_manager;
    MenuManager _menu_manager;
public:
    Launcher();
    void start();
    
    ~Launcher() noexcept = default;
    Launcher(Launcher&&) noexcept = delete;
    Launcher& operator=(Launcher&&) noexcept = delete;
    Launcher(const Launcher&) noexcept = delete;
    Launcher& operator=(const Launcher&) noexcept = delete;
};
