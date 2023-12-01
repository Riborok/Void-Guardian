// ReSharper disable CppIncompleteSwitchStatement CppDefaultCaseNotHandledInSwitchStatement CppClangTidyCppcoreguidelinesProTypeStaticCastDowncast
#include "../../../include/game/entity/EntityDeathManager.hpp"

#include "../../../include/game/executors/AnimationExecutor.hpp"

EntityDeathManager::EntityDeathManager(EntityMaps& entity_maps, ElementCreator& element_creator,
                                       AnimationExecutor& animation_executor, QuadtreeEl& quadtree):
    _entity_maps(&entity_maps), _element_creator(&element_creator), _animation_executor(&animation_executor),
    _quadtree(&quadtree) { }

void EntityDeathManager::processMurder(const Player *player) const {
    const auto& wraith = player->getWraith();
    const auto& polygon = wraith.getElement().getPolygon();
    const auto& transform_params = wraith.getElement().getTransformParams();
    _animation_executor->addAnimation(
        _element_creator->create(
            {polygon.getPoints()[0], polygon.getRotation(), ElementType::WRAITH_DYING,
                    wraith.getNum(), transform_params.scale},
                transform_params.origin
        )
    );
        
    _quadtree->remove(&player->getGun().getElement());
    _quadtree->remove(&wraith.getElement());
    _entity_maps->player_map.erase(player);  
}

void EntityDeathManager::processMurder(const Bullet *bullet) const {

    _quadtree->remove(&bullet->getElement());
    _entity_maps->bullet_map.erase(bullet);
}

void EntityDeathManager::kill(const Entity *entity) const {
    switch (ElementIdTracker::extractType(entity->getId())) {
    case ElementType::WRAITH:
        processMurder(static_cast<const Player*>(entity));
        break;
    case ElementType::BULLET:
        processMurder(static_cast<const Bullet*>(entity));
        break;
    }
}
