#pragma once
#include <random>
#include "Executor.hpp"
#include "../GameField.hpp"
#include "../../additionally/ExponentGenerator.hpp"
#include "../../additionally/LevelParameters.hpp"
#include "../../geometry/collision/CollisionManager.hpp"
#include "../construction/game field creation/arena/enemy spawn/EnemySpawnSettings.hpp"
#include "../entity/EntityMaps.hpp"
#include "../entity/bullet/BulletCreator.hpp"
#include "../entity/enemy/EnemyCreator.hpp"

struct EnemySpawnGenerator {
    ExponentGenerator gun_num_generator;
    ExponentGenerator character_num_generator;
    mutable std::uniform_real_distribution<float> bullet_spread;
    EnemySpawnSettings enemy_spawn_settings;

    explicit EnemySpawnGenerator(const size_t lvl):
        gun_num_generator(LevelParameters::createGunNumGenerator(lvl)),
        character_num_generator(LevelParameters::createEnemyCharacterNumGenerator(lvl)),
        bullet_spread(LevelParameters::getBulletSpread(lvl)),
        enemy_spawn_settings(LevelParameters::getEnemySpawnConfiguration(lvl)){}
};

class EnemyExecutor final : public Executor {
    GameField *_game_field;
    FightingMaps *_fighting_maps;
    CollisionManager *_collision_manager;
    EnemyCreator _enemy_creator;
    BulletCreator _bullet_creator;
    EnemySpawnGenerator _enemy_spawn_generator;

    SpawnPoints *_active_spawn_points = nullptr;
    
    void tryToSpawn();
    void checkSpawn(const int delta_time);
    void processPlayerCollisions(const Element& player_element) const;
    void checkEntranceToArena();
    void updateGun(const Enemy& enemy, float angle) const;
    void updateEnemies() const;
public:
    EnemyExecutor(GameField &game_field, FightingMaps &fighting_maps, CollisionManager &collision_manager,
        const EnemyCreator &enemy_creator, const BulletCreator &bullet_creator, const size_t lvl);
    
    void handle(const int delta_time) override;
    
    ~EnemyExecutor() noexcept override = default;
    EnemyExecutor(EnemyExecutor&&) noexcept = delete;
    EnemyExecutor& operator=(EnemyExecutor&&) noexcept = delete;
    EnemyExecutor(const EnemyExecutor&) noexcept = delete;
    EnemyExecutor& operator=(const EnemyExecutor&) noexcept = delete;
};
