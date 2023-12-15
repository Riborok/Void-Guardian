#pragma once

#include "GameData.hpp"
#include "GameState.hpp"
#include "GameSystem.hpp"
#include "../additionally/SimpleCreators.hpp"
#include "../files/PlayerProgress.hpp"
#include "entity/EntityMaps.hpp"
#include "executors/PlayerExecutor.hpp"
#include "input/InputHandler.hpp"
#include "processors/GameUpdater.hpp"
#include "processors/game loop/GameLoop.hpp"

class GameMaster final {
    const sf::Vector2f _player_offset_factor{-0.5, -0.5};
    
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
    
    GameSystem createGameSystem(const size_t lvl, const GameData &game_data);
    void createExecutors();
    void addPlayer(const PlayerInventory &player_inventory, const Control& control);
public:
    explicit GameMaster(sf::RenderWindow &window, const PlayerProgress &player_progress, const Control& control, const GameData &game_data);
    void start();
    GameState getGameState() const;
    PlayerInventory getPlayerInventory() const;
    
    ~GameMaster() noexcept = default;
    GameMaster(const GameMaster&) noexcept = delete;
    GameMaster& operator=(const GameMaster&) noexcept = delete;
    GameMaster(GameMaster&&) noexcept = delete;
    GameMaster& operator=(GameMaster&&) noexcept = delete;
};