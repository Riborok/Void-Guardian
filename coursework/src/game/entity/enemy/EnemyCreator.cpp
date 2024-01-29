#include "../../../../include/game/entity/enemy/EnemyCreator.hpp"

void EnemyCreator::freeEnemy(const Enemy* enemy) {
    delete &enemy->getGun().getElement();
    delete &enemy->getCharacter().getElement();
    delete enemy;
}

EnemyCreator::EnemyCreator(EntityCreator& entity_creator, CollisionHandler &collision_handler,
                           QuadtreeEl& quadtree_el):
    _entity_creator(&entity_creator), _collision_handler(&collision_handler),
    _quadtree_el(&quadtree_el) {}

Enemy* EnemyCreator::spawnEnemy(const FightingEntityInfo& entity_info) const {
    auto* enemy = _entity_creator->createEnemy(entity_info);
    if (_collision_handler->handleCollisions(enemy->getCharacter().getElement(), *_quadtree_el)) {
        if (_collision_handler->hasCollisions(enemy->getCharacter().getElement(), *_quadtree_el)) {
            freeEnemy(enemy);
            return nullptr;
        }
        enemy->getGun().update(enemy->getGunPos());
    }
    _quadtree_el->insert(&enemy->getCharacter().getElement());
    _quadtree_el->insert(&enemy->getGun().getElement());
    return enemy;
}