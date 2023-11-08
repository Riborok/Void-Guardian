#pragma once

#include "GameField.hpp"
#include "executors/PlayerExecutor.hpp"
#include "input/KeyHandler.hpp"
#include "processors/GameUpdater.hpp"
#include "processors/game loop/GameLoop.hpp"

class GameMaster final {
    sf::RenderWindow *_window;

    GameField _game_field;
    Player *_player;
    
    HotkeyManager _hotkey_manager;
    KeyHandler _key_handler;
    GameUpdater _game_updater;
    GameLoop _game_loop;
public:
    explicit GameMaster(sf::RenderWindow &window);
    void start();
    
    ~GameMaster() noexcept = default;
    
    GameMaster(const GameMaster&) noexcept = delete;
    GameMaster& operator=(const GameMaster&) noexcept = delete;
    GameMaster(GameMaster&&) noexcept = delete;
    GameMaster& operator=(GameMaster&&) noexcept = delete;
};