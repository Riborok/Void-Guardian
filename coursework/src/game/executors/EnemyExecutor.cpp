#include "../../../include/game/executors/EnemyExecutor.hpp"

#include "../../../include/additionally/LevelParameters.hpp"
#include "../../../include/game/identifiable/LocationIdTracker.hpp"

void EnemyExecutor::processFight(const int delta_time) {
}

void EnemyExecutor::processPlayerCollisions(const Element& player_element) const {
    _game_field->quadtree_el.remove(&player_element);
    ElementCollisionSet element_collision_set;
    _game_field->quadtree_el.fillCollisionSet(player_element.getPolygon(), element_collision_set);
    _collision_manager->processCollisions(player_element, element_collision_set);
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

EnemyExecutor::EnemyExecutor(GameField &game_field, Player *const& player, CollisionManager &collision_manager,
                             EnemyCreator &&enemy_creator, const size_t lvl):
    _game_field(&game_field), _player(&player), _collision_manager(&collision_manager),
    _enemy_creator(std::move(enemy_creator)), _gun_num_generator(LevelParameters::createGunNumGenerator(lvl)),
    _character_num_generator(LevelParameters::createEnemyCharacterNumGenerator(lvl)) {}

void EnemyExecutor::handle(const int delta_time) {
    if (_active_spawn_points)
        processFight(delta_time);
    else
        checkEntranceToArena();
}