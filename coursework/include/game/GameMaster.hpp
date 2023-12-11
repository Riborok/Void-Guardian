#pragma once

#include "GameData.hpp"
#include "GameField.hpp"
#include "../element/ElementCreator.hpp"
#include "construction/LocationCreator.hpp"
#include "entity/EntityCreator.hpp"
#include "entity/EntityMaps.hpp"
#include "executors/PlayerExecutor.hpp"
#include "input/InputHandler.hpp"
#include "processors/GameUpdater.hpp"
#include "processors/game loop/GameLoop.hpp"

class GameMaster final {
    ElementCreator _element_creator;
    EntityCreator _entity_creator;
    LocationCreator _location_creator;
    
    sf::RenderWindow *_window;
    GameField _game_field;
    EntityMaps _entity_maps;
    CollectibleManager _collectible_manager;
    CollisionManager _collision_manager;
    
    HotkeyManager _hotkey_manager;
    InputHandler _input_handler;
    GameUpdater _game_updater;
    GameLoop _game_loop;

    void createExecutors();
    void addPlayer();
public:
    explicit GameMaster(sf::RenderWindow &window, GameData &&game_data);
    void start();
    
    ~GameMaster() noexcept = default;
    
    GameMaster(const GameMaster&) noexcept = delete;
    GameMaster& operator=(const GameMaster&) noexcept = delete;
    GameMaster(GameMaster&&) noexcept = delete;
    GameMaster& operator=(GameMaster&&) noexcept = delete;
};