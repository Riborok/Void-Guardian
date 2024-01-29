#pragma once

#include "GameInfo.hpp"
#include "GameState.hpp"
#include "GameSystem.hpp"
#include "../GameContext.hpp"
#include "../additionally/SimpleCreators.hpp"
#include "../files/PlayerProgress.hpp"
#include "entity/EntityMaps.hpp"
#include "executors/PlayerExecutor.hpp"
#include "game handlers/GameUpdater.hpp"
#include "game handlers/game loop/GameLoop.hpp"

class GameMaster final {
    const sf::Vector2f _player_offset_factor{-0.5, -0.5};
    
    SimpleCreators _simple_creators;
    EntityCreator _entity_creator;

    GameState _game_state = GameState::PLAYING;
    sf::RenderWindow *_window;
    GameSystem _game_system;
    EntityMaps _entity_maps;
    
    GameUpdater _game_updater;
    GameLoop _game_loop;
    
    GameSystem createGameSystem(const size_t lvl, const GameInfo &game_info);
    void createExecutors(const size_t lvl);
    Player* createPlayer(const PlayerInventory &player_inventory, const Control& control);
public:
    GameMaster(GameContext &game_context, PauseSubset &pause_subset, const GameInfo &game_info);
    void start();
    [[nodiscard]] GameState getGameState() const;
    [[nodiscard]] PlayerInventory getPlayerInventory() const;
    
    ~GameMaster() noexcept = default;
    GameMaster(const GameMaster&) noexcept = delete;
    GameMaster& operator=(const GameMaster&) noexcept = delete;
    GameMaster(GameMaster&&) noexcept = delete;
    GameMaster& operator=(GameMaster&&) noexcept = delete;
};