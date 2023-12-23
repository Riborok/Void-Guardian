// ReSharper disable CppIncompleteSwitchStatement CppDefaultCaseNotHandledInSwitchStatement CppClangTidyHicppMultiwayPathsCovered
#include "../../../include/game/executors/EnemyExecutor.hpp"

#include "../../../include/game/entity/FightingEntityUtils.hpp"
#include "../../../include/game/identifiable/LocationIdTracker.hpp"
#include "../../../include/geometry/GeomAuxiliaryFunc.hpp"
#include "../../../include/geometry/Trigonometry.hpp"
#include "../../../include/model/line/Line.hpp"

void EnemyExecutor::tryToSpawn() {
    std::uniform_int_distribution<size_t> spawn_num{0, _location_state.active_spawn_points.size() - 1};
    const size_t attempt_count = _location_state.active_spawn_points.size() / 2;
    
    size_t attempt = 0;
    Enemy* enemy;
    do {
        const sf::Vector2f& spawn_point = _location_state.active_spawn_points[RandomGenerator::getRandom(spawn_num)];
        enemy = _enemy_creator.spawnEnemy(FightingEntityInfo{spawn_point, 0,
            static_cast<size_t>(_enemy_tuning_generator.character_num_generator.generate()),
            static_cast<size_t>(_enemy_tuning_generator.gun_num_generator.generate())});
        ++attempt;
    }
    while (!enemy && attempt <= attempt_count);

    if (enemy)  { _fighting_maps->enemy_map.insert(enemy); }
    else        { _enemy_tuning_generator.enemy_spawn_settings.markFailedSpawn(); }
}

void EnemyExecutor::checkSpawn(const int delta_time) {
    switch (_enemy_tuning_generator.enemy_spawn_settings.getEnemySpawnResult(delta_time)) {
    case EnemySpawnResult::SPAWN: {
        tryToSpawn();   
        break;
    }
    case EnemySpawnResult::FINISH:
        _location_state.has_active_spawn_points = false;
        break;
    }
}

void EnemyExecutor::processPlayerCollisions(const Element& player_element) const {
    _game_field->quadtree_el.remove(&player_element);
    _collision_manager->processCollisions(player_element, _game_field->quadtree_el);
    _game_field->quadtree_el.insert(&player_element);
}

bool EnemyExecutor::isEntranceToNewArena(const Element& player_element, Location* &location, SpawnMap::iterator &it) const {
    CollisionResult collision_result;
    size_t id;
    return
        // Checking that the player is in a location (and not in a transition, for example)
        (location = _game_field->quadtree_loc.getCollision(player_element.getPolygon(), collision_result)) &&
        // check, the player has entered the location almost completely
        (collision_result.overlap > player_element.calcRectDiameter() / 8) &&
        // Checking that the location is an arena    
        (id = location->getId(), LocationIdTracker::extractType(id) == RoomType::ARENA) &&
        // Checking that the player has not already been here
        ((it = _game_field->spawn_map.find(id)) != _game_field->spawn_map.end());
}

void EnemyExecutor::checkEntranceToArena() {
    if (const Player* player = _fighting_maps->player_holder.getPlayer()) {
        const Element& player_element = player->getCharacter().getElement();
        Location* location;
        if (SpawnMap::iterator it; isEntranceToNewArena(player_element, location, it)) {
            _location_state.has_active_spawn_points = true;
            _location_state.active_spawn_points = std::move(it->second);
            _game_field->spawn_map.erase(it);
            _location_state.active_location = location;
            _location_state.active_location->integrateMissingBlocks(_game_field->quadtree_el);
            processPlayerCollisions(player_element);
        }
    }
}

bool EnemyExecutor::checkMovement(const Enemy& enemy, const MovementUtils::MovementMask movement_mask, const int delta_time, sf::Vector2f &result) {
    const auto& character = enemy.getCharacter();
    const bool has_movement = MovementUtils::hasMovement(
        movement_mask,
        character.getStats().speed * static_cast<float>(delta_time),
        result
    );
    character.setSpriteIndex(has_movement);
    return has_movement;
}

void EnemyExecutor::moveEnemy(Enemy& enemy, const int delta_time) const {
    if (sf::Vector2f movement_vector; checkMovement(enemy, enemy.getMovementMask(_enemy_movement_generator), delta_time, movement_vector)) {
        const auto& element = enemy.getCharacter().getElement();

        _game_field->quadtree_el.remove(&element);
        element.move(movement_vector);
        if (_collision_manager->processCollisions(element, _game_field->quadtree_el)) { enemy.markCollision(); }
        _game_field->quadtree_el.insert(&element);
    }
}

void EnemyExecutor::shootPlayer(const Enemy& enemy, float angle) const {
    const auto& element = enemy.getCharacter().getElement();
    if (const auto& gun = enemy.getGun(); gun.canFire()) {
        angle += RandomGenerator::getRandom(_enemy_tuning_generator.bullet_spread);
        enemy.checkMirror(Trigonometry::isAngleInQuadrant2Or3(angle));
        _bullet_creator.spawnBullet(gun.fire(), element);
    }
    else if (const bool is_angle_in_quadrant2_or3(Trigonometry::isAngleInQuadrant2Or3(angle));
            FightingEntityUtils::needsMirror(element.isMirroredHor(), is_angle_in_quadrant2_or3)) {
        enemy.checkMirror(is_angle_in_quadrant2_or3);
    }
    FightingEntityUtils::updateGun(enemy.getGun(), enemy.getGunPos(), angle, _game_field->quadtree_el);
}

void EnemyExecutor::updateEnemies(const int delta_time) const {
    const auto& player = *_fighting_maps->player_holder.getPlayer();
    const auto player_center(FightingEntityUtils::calcCenter(player));
    
    for (const auto& [id, enemy] : _fighting_maps->enemy_map.getMap()) {
        moveEnemy(*enemy, delta_time);
        if (const auto enemy_center(FightingEntityUtils::calcCenter(*enemy)); _collision_manager->isVisible(
                {enemy_center, player_center}, *enemy, player, _game_field->quadtree_el)) {
            const auto destination(player_center - enemy_center);
            const float angle(GeomAuxiliaryFunc::calcAngle(destination));
            shootPlayer(*enemy, angle);
        }
        else
            FightingEntityUtils::updateGun(enemy->getGun(), enemy->getGunPos(), _game_field->quadtree_el);
    }
}

EnemyExecutor::EnemyExecutor(GameField &game_field, FightingMaps &fighting_maps,
        CollisionManager &collision_manager, const EnemyCreator &enemy_creator, const BulletCreator &bullet_creator,
        const size_t lvl):
    _game_field(&game_field), _fighting_maps(&fighting_maps), _collision_manager(&collision_manager),
    _enemy_creator(enemy_creator), _bullet_creator(bullet_creator),
    _enemy_tuning_generator(lvl) {}

void EnemyExecutor::handle(const int delta_time) {
    if (_fighting_maps->player_holder.getPlayer()) {
        if (const bool has_enemies(!_fighting_maps->enemy_map.getMap().empty());
                _location_state.has_active_spawn_points || has_enemies) {
            if (_location_state.has_active_spawn_points)
                checkSpawn(delta_time);
            if (has_enemies)
                updateEnemies(delta_time);   
        }
        else if (_location_state.active_location) {
            _location_state.active_location->excludeMissingBlocks(_game_field->quadtree_el);
            _location_state.active_location = nullptr;
        }
        else
            checkEntranceToArena();
    }
}