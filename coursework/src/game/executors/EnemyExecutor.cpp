// ReSharper disable CppIncompleteSwitchStatement CppDefaultCaseNotHandledInSwitchStatement CppClangTidyHicppMultiwayPathsCovered
#include "../../../include/game/executors/EnemyExecutor.hpp"

#include "../../../include/game/entity/FightingEntityUtils.hpp"
#include "../../../include/game/identifiable/LocationIdTracker.hpp"
#include "../../../include/geometry/GeomAuxiliaryFunc.hpp"
#include "../../../include/geometry/Trigonometry.hpp"
#include "../../../include/model/line/Line.hpp"

void EnemyExecutor::tryToSpawn() {
    std::uniform_int_distribution<size_t> spawn_num{0, _active_spawn_points->size() - 1};
    const size_t attempt_count = _active_spawn_points->size() / 2;
    
    size_t attempt = 0;
    Enemy* enemy;
    do {
        const sf::Vector2f& spawn_point = (*_active_spawn_points)[RandomGenerator::getRandom(spawn_num)];
        enemy = _enemy_creator.spawnEnemy(FightingEntityInfo{spawn_point, 0,
            static_cast<size_t>(_enemy_spawn_generator.character_num_generator.generate()),
            static_cast<size_t>(_enemy_spawn_generator.gun_num_generator.generate())});
        ++attempt;
    }
    while (!enemy && attempt <= attempt_count);

    if (enemy)  { _fighting_maps->enemy_map.insert(enemy); }
    else        { _enemy_spawn_generator.enemy_spawn_settings.recordFailedSpawn(); }
}

void EnemyExecutor::checkSpawn(const int delta_time) {
    switch (_enemy_spawn_generator.enemy_spawn_settings.getEnemySpawnResult(delta_time)) {
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
    if (const Player* player = _fighting_maps->player_holder.getPlayer()) {
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

void EnemyExecutor::updateGun(const Enemy& enemy, float angle) const {
    const auto& element = enemy.getCharacter().getElement();
    if (const auto& gun = enemy.getGun(); gun.canFire()) {
        angle += RandomGenerator::getRandom(_enemy_spawn_generator.bullet_spread);
        enemy.checkMirror(Trigonometry::isAngleInQuadrant2Or3(angle));
        FightingEntityUtils::updateGun(enemy.getGun(), enemy.getGunPos(), angle, _game_field->quadtree_el);
        _bullet_creator.spawnBullet(gun.fire(), element);
    }
    else if (const bool is_angle_in_quadrant2_or3(Trigonometry::isAngleInQuadrant2Or3(angle));
            FightingEntityUtils::needsMirror(element.isMirroredHor(), is_angle_in_quadrant2_or3)) {
        enemy.checkMirror(is_angle_in_quadrant2_or3);
        FightingEntityUtils::updateGun(enemy.getGun(), enemy.getGunPos(), angle, _game_field->quadtree_el);
    }
}

void EnemyExecutor::updateEnemies() const {
    const auto& player = *_fighting_maps->player_holder.getPlayer();
    const auto player_center(FightingEntityUtils::calcCenter(player));
    
    for (const auto& [id, enemy] : _fighting_maps->enemy_map.getMap())
        if (const auto enemy_center(FightingEntityUtils::calcCenter(*enemy)); _collision_manager->isVisible(
                {enemy_center, player_center}, *enemy, player, _game_field->quadtree_el)) {
            const auto destination(player_center - enemy_center);
            const float angle(GeomAuxiliaryFunc::calcAngle(destination));
            updateGun(*enemy, angle);
        }
}

EnemyExecutor::EnemyExecutor(GameField &game_field, FightingMaps &fighting_maps,
        CollisionManager &collision_manager, const EnemyCreator &enemy_creator, const BulletCreator &bullet_creator,
        const size_t lvl):
    _game_field(&game_field), _fighting_maps(&fighting_maps), _collision_manager(&collision_manager),
    _enemy_creator(enemy_creator), _bullet_creator(bullet_creator),
    _enemy_spawn_generator(lvl) {}

void EnemyExecutor::handle(const int delta_time) {
    if (_fighting_maps->player_holder.getPlayer()) {
        if (const bool has_enemies(!_fighting_maps->enemy_map.getMap().empty()); _active_spawn_points || has_enemies) {
            if (_active_spawn_points)
                checkSpawn(delta_time);
            if (has_enemies)
                updateEnemies();   
        }
        else
            checkEntranceToArena();
    }
}