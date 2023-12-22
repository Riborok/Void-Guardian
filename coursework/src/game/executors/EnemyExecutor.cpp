// ReSharper disable CppIncompleteSwitchStatement CppDefaultCaseNotHandledInSwitchStatement CppClangTidyHicppMultiwayPathsCovered
#include "../../../include/game/executors/EnemyExecutor.hpp"

#include "../../../include/additionally/LevelParameters.hpp"
#include "../../../include/game/identifiable/LocationIdTracker.hpp"

void EnemyExecutor::tryToSpawn() {
    std::uniform_int_distribution<size_t> spawn_num{0, _active_spawn_points->size() - 1};
    const size_t attempt_count = _active_spawn_points->size() / 2;
    
    size_t attempt = 0;
    Enemy* enemy;
    do {
        const sf::Vector2f& spawn_point = (*_active_spawn_points)[RandomGenerator::getRandom(spawn_num)];
        enemy = _enemy_creator.spawnEnemy(FightingEntityInfo{spawn_point, 0,
            static_cast<size_t>(_character_num_generator.generate()),
            static_cast<size_t>(_gun_num_generator.generate())});
        ++attempt;
    }
    while (!enemy && attempt <= attempt_count);

    if (enemy)  { _enemy_map->insert(enemy); }
    else        { _enemy_spawn_settings.recordFailedSpawn(); }
}

void EnemyExecutor::checkSpawn(const int delta_time) {
    switch (_enemy_spawn_settings.getEnemySpawnResult(delta_time)) {
    case EnemySpawnResult::SPAWN: {
        tryToSpawn();   
        break;
    }
    case EnemySpawnResult::FINISH:
        _active_spawn_points = nullptr;
        break;
    }
}

void EnemyExecutor::processPlayerCollisions(const Element& player_element) const {
    _game_field->quadtree_el.remove(&player_element);
    _collision_manager->processCollisions(player_element, _game_field->quadtree_el);
    _game_field->quadtree_el.insert(&player_element);
}

void EnemyExecutor::checkEntranceToArena() {
    if (const Player* player = *_player) {
        CollisionResult collision_result;
        const Element& player_element = player->getCharacter().getElement();
        if (Location* location = _game_field->quadtree_loc.getCollision(player_element.getPolygon(), collision_result)) {
            if (const size_t id = location->getId(); LocationIdTracker::extractType(id) == RoomType::ARENA &&
                    collision_result.overlap > player_element.calcRectDiameter() / 8) {
                _active_spawn_points = &_game_field->spawn_map[id];
                location->integrateMissingBlocks(_game_field->quadtree_el);
                processPlayerCollisions(player_element);
            }
        }
    }
}

EnemyExecutor::EnemyExecutor(GameField &game_field, EnemyMap &enemy_map, Player *const& player,
        CollisionManager &collision_manager, EnemyCreator &&enemy_creator, const size_t lvl):
    _game_field(&game_field), _enemy_map(&enemy_map), _player(&player), _collision_manager(&collision_manager),
    _enemy_creator(std::move(enemy_creator)),
    _enemy_spawn_settings(LevelParameters::getEnemySpawnConfiguration(lvl)),
    _gun_num_generator(LevelParameters::createGunNumGenerator(lvl)),
    _character_num_generator(LevelParameters::createEnemyCharacterNumGenerator(lvl)) {}

void EnemyExecutor::handle(const int delta_time) {
    if (_active_spawn_points || !_enemy_map->getMap().empty()) {
        checkSpawn(delta_time);
    }
    else
        checkEntranceToArena();
}