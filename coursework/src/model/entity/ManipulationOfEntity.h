#pragma once

#include "Entity.h"
#include "../../geometry/Trigonometry.h"
#include "../../geometry/Vector2Rotation.h"

namespace ManipulationOfEntity {
    inline void EntityMovement(Entity &entity) {
        const sf::Vector2f &velocity = entity.Velocity();
        sf::Vector2f *points = entity.Points();
        const size_t &amount = entity.PointsAmount();
    
        for (size_t i = 0; i < amount; ++i) {
            points[i].x += velocity.x;
            points[i].y += velocity.y;
        }
    }

    inline void RotateEntity(Entity &entity, const float delta_angle) {
        const float sin = SIN_DEGREES(delta_angle);
        const float cos = COS_DEGREES(delta_angle);
        const sf::Vector2f center = entity.CalcCenter();

        sf::Vector2f *points = entity.Points();
        const size_t &amount = entity.PointsAmount();
        for (size_t i = 0; i < amount; ++i)
            Vector2Rotation::RotateVector2AroundTarget(points[i], center, sin, cos);
    
        Vector2Rotation::RotateVector2(entity.Velocity(), sin, cos);
    }

    inline void EntityAngularMovement(Entity &entity) {
        RotateEntity(entity, entity.GetAngularVelocity());
    }
}