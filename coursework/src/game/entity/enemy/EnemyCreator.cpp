#include "../../../../include/game/entity/enemy/EnemyCreator.hpp"

EnemyCreator::EnemyCreator(EnemyMap& enemy_map, EntityCreator& entity_creator, QuadtreeEl& quadtree_el):
    _enemy_map(&enemy_map), _entity_creator(&entity_creator), _quadtree_el(&quadtree_el) {}

void EnemyCreator::spawnEnemy(const FightingEntityInfo& player_info) const {
    auto* player = _entity_creator->createEnemy(player_info);
    _enemy_map->insert(player);
    _quadtree_el->insert(&player->getCharacter().getElement());
    _quadtree_el->insert(&player->getGun().getElement());
}