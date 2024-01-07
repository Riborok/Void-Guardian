#pragma once

#include "GameData.hpp"
#include "GameState.hpp"
#include "GameSystem.hpp"
#include "../GameContext.hpp"
#include "../additionally/SimpleCreators.hpp"
#include "../files/PlayerProgress.hpp"
#include "entity/EntityMaps.hpp"
#include "executors/PlayerExecutor.hpp"
#include "processors/GameUpdater.hpp"
#include "processors/game loop/GameLoop.hpp"

class GameMaster final {
    const sf::Vector2f _player_offset_factor{-0.5, -0.5};
    
    SimpleCreators _simple_creators;
    EntityCreator _entity_creator;

    GameState _game_state = GameState::PLAYING;
    sf::RenderWindow *_window;
    GameSystem _game_system;
    EntityMaps _entity_maps;
    
    HotkeyManager _hotkey_manager;
    GameUpdater _game_updater;
    GameLoop _game_loop;
    
    GameSystem createGameSystem(const size_t lvl, const GameData &game_data);
    void createExecutors(const size_t lvl);
    Player* createPlayer(const PlayerInventory &player_inventory, const Control& control);
public:
    GameMaster(GameContext &game_context, const GameData &game_data);
    void start();
    [[nodiscard]] GameState getGameState() const;
    [[nodiscard]] PlayerInventory getPlayerInventory() const;
    
    ~GameMaster() noexcept = default;
    GameMaster(const GameMaster&) noexcept = delete;
    GameMaster& operator=(const GameMaster&) noexcept = delete;
    GameMaster(GameMaster&&) noexcept = delete;
    GameMaster& operator=(GameMaster&&) noexcept = delete;
};