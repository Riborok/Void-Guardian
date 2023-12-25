#pragma once
#include "files/FileManager.hpp"
#include "game/GameState.hpp"
#include "game/input/FullscreenToggler.hpp"
#include "gui/MenuManager.hpp"

// TODO: Make a normal launcher
class Launcher final {
    sf::RenderWindow _window;
    FullscreenToggler _fullscreen_toggler;
    FileManager _file_manager;
    PlayerProgress _player_progress;
    Control _control;
    MenuManager _menu_manager;

    void setDefaultTitle();
    void startMenu();
    void setLvlTitle();
    GameState startGame();
public:
    Launcher();
    void start();
    
    ~Launcher() noexcept = default;
    Launcher(Launcher&&) noexcept = delete;
    Launcher& operator=(Launcher&&) noexcept = delete;
    Launcher(const Launcher&) noexcept = delete;
    Launcher& operator=(const Launcher&) noexcept = delete;
};
