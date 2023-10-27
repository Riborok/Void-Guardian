#pragma once

#include "input/KeyHandler.h"

class GameMaster final {
    KeyHandler _key_handler;
    sf::RenderWindow &_window;
public:
    explicit GameMaster(sf::RenderWindow &window): _window(window) { }

    KeyHandler &keyHandler() { return _key_handler; }

    ~GameMaster() noexcept = default;
    
    GameMaster(const GameMaster&) noexcept = delete;
    GameMaster& operator=(const GameMaster&) noexcept = delete;
    GameMaster(GameMaster&&) noexcept = delete;
    GameMaster& operator=(GameMaster&&) noexcept = delete;
};
