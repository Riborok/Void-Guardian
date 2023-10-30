#pragma once

#include "Entity.h"
#include "../../geometry/Trigonometry.h"
#include "../../geometry/Vector2Rotation.h"

namespace ManipulationOfEntity {
    /**
     * Move an entity based on its current velocity.
     * @param entity The entity to move.
     * @warning If the entity moves a distance greater than its own size, it may lead to collision processing errors.
     */
    inline void entityMovement(Entity &entity) {
        const sf::Vector2f &velocity = entity.velocity();
        sf::Vector2f *points = entity.points();
        const size_t amount = entity.pointsAmount();
    
        for (size_t i = 0; i < amount; ++i) {
            points[i].x += velocity.x;
            points[i].y += velocity.y;
        }
    }

    /**
     * Rotate an entity by a specified angle (in radians) in radians around its center point.
     * @param entity The entity to rotate.
     * @param delta_angle The angle (in radians) by which to rotate the entity.
     */
    inline void rotateEntity(Entity &entity, const float delta_angle) {
        const float sin = SIN_DEGREES(delta_angle);
        const float cos = COS_DEGREES(delta_angle);
        const sf::Vector2f center = entity.calcCenter();

        sf::Vector2f *points = entity.points();
        const size_t amount = entity.pointsAmount();
        for (size_t i = 0; i < amount; ++i)
            Vector2Rotation::rotateVector2AroundTarget(points[i], center, sin, cos);
    
        Vector2Rotation::rotateVector2(entity.velocity(), sin, cos);
    }

    /**
     * Rotate an entity based on its current angular velocity.
     * @param entity The entity to rotate.
     * @warning If the entity moves a distance greater than its own size, it may lead to collision processing errors.
     */
    inline void entityAngularMovement(Entity &entity) {
        rotateEntity(entity, entity.getAngularVelocity());
    }
}