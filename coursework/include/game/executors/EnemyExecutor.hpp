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

class EnemyExecutor final : public Executor {
    struct EnemyTuningGenerator final {
        ExponentGenerator gun_num_generator;
        ExponentGenerator character_num_generator;
        mutable std::uniform_real_distribution<float> bullet_spread;
        EnemySpawnSettings enemy_spawn_settings;

        explicit EnemyTuningGenerator(const size_t lvl):
            gun_num_generator(LevelParameters::createGunNumGenerator(lvl)),
            character_num_generator(LevelParameters::createEnemyCharacterNumGenerator(lvl)),
            bullet_spread(LevelParameters::getBulletSpread(lvl)),
            enemy_spawn_settings(LevelParameters::getEnemySpawnConfiguration(lvl)){}
    };
    struct LocationState final {
        Location *active_location;
        SpawnPoints active_spawn_points;
        bool has_active_spawn_points;
        LocationState(): active_location(nullptr), has_active_spawn_points(false) {}
    };
    
    GameField *_game_field;
    FightingMaps *_fighting_maps;
    CollisionManager *_collision_manager;
    EnemyCreator _enemy_creator;
    BulletCreator _bullet_creator;
    EnemyTuningGenerator _enemy_tuning_generator;
    LocationState _location_state;

    // TODO: Make normal bot movement logic
    EnemyMovementGenerator _enemy_movement_generator;
    // TODO: Make normal bot movement logic
    static bool checkMovement(const Enemy& enemy, const MovementUtils::MovementMask movement_mask,
                              const int delta_time, sf::Vector2f &result);
    // TODO: Make normal bot movement logic
    void moveEnemy(Enemy& enemy, const int delta_time) const;
    
    void tryToSpawn();
    void checkSpawn(const int delta_time);
    void processPlayerCollisions(const Element& player_element) const;
    bool isEntranceToNewArena(const Element& player_element, Location* &location, SpawnMap::iterator &it) const;
    void checkEntranceToArena();
    void shootPlayer(const Enemy& enemy, float angle) const;
    void updateEnemies(const int delta_time) const;
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