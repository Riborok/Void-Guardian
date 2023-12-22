#include "../../../../include/game/entity/enemy/EnemyCreator.hpp"

EnemyCreator::EnemyCreator(EntityCreator& entity_creator, CollisionManager &collision_manager,
        QuadtreeEl& quadtree_el):
    _entity_creator(&entity_creator), _collision_manager(&collision_manager),
    _quadtree_el(&quadtree_el) {}

Enemy* EnemyCreator::spawnEnemy(const FightingEntityInfo& entity_info) const {
    auto* enemy = _entity_creator->createEnemy(entity_info);
    if (_collision_manager->processCollisions(enemy->getCharacter().getElement(), *_quadtree_el))
        enemy->getGun().update(enemy->getGunPos(), entity_info.angle);
    _quadtree_el->insert(&enemy->getCharacter().getElement());
    _quadtree_el->insert(&enemy->getGun().getElement());
    return enemy;
}