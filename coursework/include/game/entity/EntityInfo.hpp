#pragma once
#include <SFML/System/Vector2.hpp>

struct EntityInfo final {
    int health;
    int armor;
    float armor_strength;
    EntityInfo(const int health, const int armor, const float armor_strength) :
        health(health), armor(armor), armor_strength(armor_strength) { }
};

template <typename T>
struct EntityData final {
    T data;
    EntityInfo entity_info;
    sf::Vector2f scale;
    EntityData(const T& data, const EntityInfo& entity_info, const sf::Vector2f &scale):
        data(data), entity_info(entity_info), scale(scale) {}
};

template <typename T>
struct EntityPartData final {
    T data;
    sf::Vector2f scale;
    EntityPartData(const T& data, const sf::Vector2f &scale): data(data), scale(scale) {}
};