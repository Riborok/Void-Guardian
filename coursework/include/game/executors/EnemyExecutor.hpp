#pragma once
#include "Executor.hpp"
#include "../GameField.hpp"
#include "../entity/player/PlayerMap.hpp"

class EnemyExecutor final : public Executor {
    
    GameField *_game_field;
    PlayerMap *_player_map;
public:

    void handle(const int delta_time) override;
    ~EnemyExecutor() noexcept override = default;
    EnemyExecutor(EnemyExecutor&&) noexcept = delete;
    EnemyExecutor& operator=(EnemyExecutor&&) noexcept = delete;
    EnemyExecutor(const EnemyExecutor&) noexcept = delete;
    EnemyExecutor& operator=(const EnemyExecutor&) noexcept = delete;
};
