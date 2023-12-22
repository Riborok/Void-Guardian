#pragma once
#include "Executor.hpp"
#include "../GameField.hpp"
#include "../../additionally/ExponentGenerator.hpp"
#include "../../geometry/collision/CollisionManager.hpp"
#include "../construction/game field creation/arena/enemy spawn/EnemySpawnSettings.hpp"
#include "../entity/enemy/EnemyCreator.hpp"
#include "../entity/enemy/EnemyMap.hpp"

class EnemyExecutor final : public Executor {
    GameField *_game_field;
    EnemyMap *_enemy_map;
    Player *const* _player;
    CollisionManager *_collision_manager;
    EnemyCreator _enemy_creator;
    EnemySpawnSettings _enemy_spawn_settings;
    ExponentGenerator _gun_num_generator;
    ExponentGenerator _character_num_generator;

    SpawnPoints *_active_spawn_points = nullptr;

    void tryToSpawn();
    void checkSpawn(const int delta_time);
    void processPlayerCollisions(const Element& player_element) const;
    void checkEntranceToArena();
public:
    EnemyExecutor(GameField &game_field, EnemyMap &enemy_map, Player *const& player, CollisionManager &collision_manager,
        EnemyCreator &&enemy_creator, const size_t lvl);
    
    void handle(const int delta_time) override;
    
    ~EnemyExecutor() noexcept override = default;
    EnemyExecutor(EnemyExecutor&&) noexcept = delete;
    EnemyExecutor& operator=(EnemyExecutor&&) noexcept = delete;
    EnemyExecutor(const EnemyExecutor&) noexcept = delete;
    EnemyExecutor& operator=(const EnemyExecutor&) noexcept = delete;
};
