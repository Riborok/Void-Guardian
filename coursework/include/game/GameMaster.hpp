#pragma once

#include "GameData.hpp"
#include "GameState.hpp"
#include "GameSystem.hpp"
#include "../additionally/SimpleCreators.hpp"
#include "entity/EntityMaps.hpp"
#include "executors/PlayerExecutor.hpp"
#include "input/InputHandler.hpp"
#include "processors/GameUpdater.hpp"
#include "processors/game loop/GameLoop.hpp"

class GameMaster final {
    SimpleCreators _simple_creators;
    EntityCreator _entity_creator;

    GameState _game_state = GameState::PLAYING;
    sf::RenderWindow *_window;
    EntityMaps _entity_maps;
    GameSystem _game_system;
    
    HotkeyManager _hotkey_manager;
    InputHandler _input_handler;
    GameUpdater _game_updater;
    GameLoop _game_loop;

    GameSystem createGameSystem(const GameData &game_data);
    void createExecutors();
    void addPlayer();
public:
    explicit GameMaster(sf::RenderWindow &window, const GameData &game_data);
    GameState start();
    
    ~GameMaster() noexcept = default;
    
    GameMaster(const GameMaster&) noexcept = delete;
    GameMaster& operator=(const GameMaster&) noexcept = delete;
    GameMaster(GameMaster&&) noexcept = delete;
    GameMaster& operator=(GameMaster&&) noexcept = delete;
};