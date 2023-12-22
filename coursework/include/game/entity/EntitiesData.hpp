#pragma once
#include <SFML/System/Vector2.hpp>
#include "EntityInfo.hpp"

template <typename T>
struct EntitiesPartData {
    T data;
    sf::Vector2f scale;
    EntitiesPartData(const T& data, const sf::Vector2f &scale): data(data), scale(scale) {}
};

template <typename T>
struct EntitiesData : EntitiesPartData<T> {
    EntityInfo entity_info;
    EntitiesData(const T& data_, const EntityInfo& entity_info, const sf::Vector2f &scale_):
        EntitiesPartData<T>(data_, scale_), entity_info(entity_info){}
};

template <typename T>
struct FightingEntitiesData final : EntitiesData<T> {
    sf::Vector2f gun_offset;
    FightingEntitiesData(const T& data_, const EntityInfo& entity_info_, const sf::Vector2f &gun_offset, const sf::Vector2f &scale_):
        EntitiesData<T>(data_, entity_info_, scale_),  gun_offset(gun_offset) {}
};