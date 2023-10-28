#pragma once
#include <SFML/System/Vector2.hpp>

#include "../polygon/Polygon.h"

class Entity : public Polygon {
protected:
    float _angular_velocity;
    sf::Vector2f _velocity;
public:
    ~Entity() noexcept override = default;
    
    sf::Vector2f &velocity() { return _velocity; }
    
    float getAngularVelocity() const { return _angular_velocity; }
    void setAngularVelocity(const float value) { _angular_velocity = value; }
    
    Entity(const Entity&) noexcept = delete;
    Entity& operator=(const Entity&) noexcept = delete;
    Entity(Entity&&) noexcept = delete;
    Entity& operator=(Entity&&) noexcept = delete;
protected:
    explicit Entity() : _angular_velocity(0.0f), _velocity(0, 0){ }
};
