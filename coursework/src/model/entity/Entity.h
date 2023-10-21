#pragma once
#include <SFML/System/Vector2.hpp>

#include "../polygon/IdPolygon.h"

class Entity : public IdPolygon {
protected:
    float _angular_velocity;
    sf::Vector2f _velocity;
public:
    virtual ~Entity() noexcept override = default;
    
    sf::Vector2f &Velocity() { return _velocity; }
    
    float GetAngularVelocity() const { return _angular_velocity; }
    void SetAngularVelocity(const float value) { _angular_velocity = value; }
    
    Entity(const Entity&) noexcept = default;
    Entity& operator=(const Entity&) noexcept = default;
    Entity(Entity&&) noexcept = default;
    Entity& operator=(Entity&&) noexcept = default;
protected:
    explicit Entity(const int id) : IdPolygon(id), _angular_velocity(0), _velocity(0, 0){ }
};