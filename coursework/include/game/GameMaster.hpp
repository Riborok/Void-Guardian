#pragma once

#include "GameData.hpp"
#include "GameField.hpp"
#include "../element/ElementCreator.hpp"
#include "construction/LocationCreator.hpp"
#include "entity/EntityCreator.hpp"
#include "executors/PlayerExecutor.hpp"
#include "input/KeyHandler.hpp"
#include "processors/GameUpdater.hpp"
#include "processors/game loop/GameLoop.hpp"

class GameMaster final {
    ElementCreator _element_creator;
    EntityCreator _entity_creator;
    LocationCreator _location_creator;
    
    sf::RenderWindow *_window;

    GameField _game_field;
    CollisionManager _collision_manager;
    Player *_player;
    
    HotkeyManager _hotkey_manager;
    KeyHandler _key_handler;
    GameUpdater _game_updater;
    GameLoop _game_loop;
public:
    explicit GameMaster(sf::RenderWindow &window, GameData &&game_data);
    void start();
    
    ~GameMaster() noexcept = default;
    
    GameMaster(const GameMaster&) noexcept = delete;
    GameMaster& operator=(const GameMaster&) noexcept = delete;
    GameMaster(GameMaster&&) noexcept = delete;
    GameMaster& operator=(GameMaster&&) noexcept = delete;
};