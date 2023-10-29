#pragma once

#include "Entity.h"
#include "../../geometry/Trigonometry.h"
#include "../../geometry/Vector2Rotation.h"

namespace ManipulationOfEntity {
    inline void entityMovement(Entity &entity) {
        const sf::Vector2f &velocity = entity.velocity();
        sf::Vector2f *points = entity.points();
        const size_t amount = entity.pointsAmount();
    
        for (size_t i = 0; i < amount; ++i) {
            points[i].x += velocity.x;
            points[i].y += velocity.y;
        }
    }

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

    inline void entityAngularMovement(Entity &entity) {
        rotateEntity(entity, entity.getAngularVelocity());
    }
}