#include "../../../include/game/entity/DyingEffectAnimator.hpp"

#include "../../../include/element/ElementType.hpp"
#include "../../../include/game/executors/AnimationExecutor.hpp"
#include "../../../include/geometry/collision/CollisionDetection.hpp"
#include "../../../include/geometry/collision/CollisionResult.hpp"

const sf::Vector2f DyingEffectAnimator::OFFSET_FACTOR = {-1.0f, -0.5f};

DyingEffectAnimator::DyingEffectAnimator(ElementCreator& element_creator, AnimationExecutor& animation_executor):
    _element_creator(&element_creator), _animation_executor(&animation_executor) {}

void DyingEffectAnimator::createAnimation(const Player& player) const {
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

void DyingEffectAnimator::createAnimation(const Bullet& bullet, const Polygon& murder_polygon) const {
    CollisionResult collision_result;
    CollisionDetection::getCollisionResult(bullet.getElement().getPolygon(), murder_polygon, collision_result);
    
    const auto& polygon = bullet.getElement().getPolygon();
    _animation_executor->addAnimation(_element_creator->create(
        {
            collision_result.collision_point,
            polygon.getRotation(),
            ElementType::BULLET_IMPACT,
            AdditionalFunc::getRandom(_num),
            bullet.getElement().getTransformParams().scale * SCALE_FACTOR
        },
        OFFSET_FACTOR
    ));
}
