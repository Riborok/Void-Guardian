// ReSharper disable CppIncompleteSwitchStatement CppDefaultCaseNotHandledInSwitchStatement CppClangTidyCppcoreguidelinesProTypeStaticCastDowncast CppNoDiscardExpression
#include "../../../include/game/entity/EntityDamageManager.hpp"

#include "../../../include/game/executors/AnimationExecutor.hpp"

EntityDamageManager::EntityDamageManager(EntityMaps& entity_maps, ElementCreator& element_creator,
                                       AnimationExecutor& animation_executor, QuadtreeEl& quadtree):
    _entity_maps(&entity_maps), _element_creator(&element_creator), _animation_executor(&animation_executor),
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

void EntityDamageManager::createAnimation(const Player &player) const {
    const auto& wraith = player.getWraith();
    const auto& polygon = wraith.getElement().getPolygon();
    _animation_executor->addAnimation(_element_creator->create({
        polygon.getPoints()[0],
        polygon.getRotation(),
        ElementType::WRAITH_DYING,
        wraith.getNum(),
        player.getWraith().getElement().getTransformParams().scale
    }));
}

void EntityDamageManager::createAnimation(const Bullet &bullet) const {
    
}

void EntityDamageManager::applyDamage(const BulletStats &bullet_stats, const ElementCollisionSet &hits) const {
    for (const auto& hit : hits) {
        switch (const size_t id = hit->getId(); ElementIdTracker::extractType(id)) {
        case ElementType::WRAITH: {
            auto *entity = _entity_maps->player_map.getMap().at(id);
            entity->takeDamage(bullet_stats);

            if (entity->isDead()) {
                createAnimation(*entity);
                erase(entity);
            }
            break;
        }
        case ElementType::BULLET: {
            auto *other_bullet = _entity_maps->bullet_map.getMap().at(id);
            other_bullet->takeDamage(bullet_stats);

            if (other_bullet->isDead()) {
                createAnimation(*other_bullet);
                erase(other_bullet);
            }
            break;
        }
        }
    }
}