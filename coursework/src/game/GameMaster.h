#pragma once

#include "controls/SpriteDrawer.h"
#include "input/KeyHandler.h"

class GameMaster final {
    KeyHandler _key_handler;
    SpriteDrawer _sprite_drawer;
public:
    explicit GameMaster(sf::RenderWindow &window): _sprite_drawer(window) { }

    KeyHandler &keyHandler() { return _key_handler; }

    ~GameMaster() noexcept = default;
    
    GameMaster(const GameMaster&) noexcept = delete;
    GameMaster& operator=(const GameMaster&) noexcept = delete;
    GameMaster(GameMaster&&) noexcept = delete;
    GameMaster& operator=(GameMaster&&) noexcept = delete;
};
