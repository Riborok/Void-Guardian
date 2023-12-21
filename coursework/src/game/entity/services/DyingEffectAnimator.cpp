#include "../../../../include/game/entity/services/DyingEffectAnimator.hpp"

DyingEffectAnimator::DyingEffectAnimator(ElementCreator& element_creator, AnimationManager &animation_manager):
    _element_creator(&element_creator), _animation_manager(&animation_manager) {}

void DyingEffectAnimator::createAnimation(const FightingEntity &entity) const {
    const auto& character = entity.getCharacter();
    const auto& polygon = character.getElement().getPolygon();
    _animation_manager->addAnimation(_element_creator->create({
        polygon.getPoints()[0],
        polygon.getRotation(),
        ElementType::CHARACTER_DYING,
        character.getNum(),
        character.getElement().getTransformParams().scale
    }));
}

void DyingEffectAnimator::createAnimation(const Bullet& bullet, const Polygon& murder_polygon) const {
    CollisionResult collision_result;
    const auto& element = bullet.getBulletCasing().getElement();
    const auto& polygon = element.getPolygon();
    CollisionDetection::getCollisionResult(polygon, murder_polygon, collision_result);
    
    _animation_manager->addAnimation(_element_creator->create(
        {
            collision_result.collision_point,
            polygon.getRotation(),
            ElementType::BULLET_IMPACT,
            RandomGenerator::getRandom(_num),
            element.getTransformParams().scale * SCALE_FACTOR
        },
        _offset_factor
    ));
}