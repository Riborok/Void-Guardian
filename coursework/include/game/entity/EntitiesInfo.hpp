#pragma once
#include <SFML/System/Vector2.hpp>
#include "EntityInfo.hpp"

template <typename T>
struct EntitiesPartInfo {
    T info;
    sf::Vector2f scale;
    EntitiesPartInfo(const T& info, const sf::Vector2f &scale): info(info), scale(scale) {}
};

template <typename T>
struct EntitiesInfo : EntitiesPartInfo<T> {
    EntityInfo entity_info;
    EntitiesInfo(const T& info_, const EntityInfo& entity_info, const sf::Vector2f &scale_):
        EntitiesPartInfo<T>(info_, scale_), entity_info(entity_info){}
};

template <typename T>
struct FightingEntitiesInfo final : EntitiesInfo<T> {
    sf::Vector2f gun_offset;
    FightingEntitiesInfo(const T& info_, const EntityInfo& entity_info_, const sf::Vector2f &gun_offset, const sf::Vector2f &scale_):
        EntitiesInfo<T>(info_, entity_info_, scale_),  gun_offset(gun_offset) {}
};