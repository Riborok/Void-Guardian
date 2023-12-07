// ReSharper disable CppIncompleteSwitchStatement CppDefaultCaseNotHandledInSwitchStatement CppClangTidyCppcoreguidelinesProTypeStaticCastDowncast CppNoDiscardExpression
#include "../../../include/game/entity/EntityDamageManager.hpp"

#include "../../../include/game/executors/AnimationExecutor.hpp"

EntityDamageManager::EntityDamageManager(EntityMaps& entity_maps, ElementCreator& element_creator,
                                         AnimationExecutor& animation_executor, QuadtreeEl& quadtree):
    _entity_maps(&entity_maps), _dying_effect_animator(element_creator, animation_executor),
    _quadtree(&quadtree) { }

void EntityDamageManager::erase(const Player *player) const {
    _quadtree->remove(&player->getGun().getElement());
    _quadtree->remove(&player->getWraith().getElement());
    _entity_maps->player_map.erase(player);  
}

void EntityDamageManager::erase(const Bullet *bullet) const {
    _quadtree->remove(&bullet->getElement());
    _entity_maps->bullet_map.erase(bullet);
}

void EntityDamageManager::applyDamage(const Bullet &bullet, const ElementCollisionSet &hits) const {
    for (const auto* hit : hits) {
        switch (const size_t id = hit->getId(); ElementIdTracker::extractType(id)) {
        case ElementType::WRAITH: {
            auto *entity = _entity_maps->player_map.getMap().at(id);
            entity->takeDamage(bullet.getStats());

            if (entity->isDead()) {
                _dying_effect_animator.createAnimation(*entity);
                erase(entity);
            }
            break;
        }
        case ElementType::BULLET: {
            auto *other_bullet = _entity_maps->bullet_map.getMap().at(id);
            other_bullet->takeDamage(bullet.getStats());

            if (other_bullet->isDead()) {
                _dying_effect_animator.createAnimation(*other_bullet, bullet.getElement().getPolygon());
                erase(other_bullet);
            }
            break;
        }
        }
    }
}

const DyingEffectAnimator& EntityDamageManager::getDyingAnimator() const{ return _dying_effect_animator; }