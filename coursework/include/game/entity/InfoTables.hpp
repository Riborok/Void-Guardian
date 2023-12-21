#pragma once
#include <array>

#include "EntityInfo.hpp"
#include "bullet/BulletInfo.hpp"
#include "component/character/CharacterStats.hpp"
#include "component/gun/GunInfo.hpp"

constexpr size_t CHARACTER_COUNT = 4;
constexpr size_t GUN_COUNT = 16;
constexpr size_t BULLET_COUNT = GUN_COUNT;

typedef std::array<EntityData<CharacterStats>, CHARACTER_COUNT> CharacterInfos;
typedef std::array<EntityPartData<GunInfo>, GUN_COUNT> GunInfos;
typedef std::array<EntityData<BulletInfo>, BULLET_COUNT> BulletInfos;

struct EntityInfoTables final {
    CharacterInfos character_infos;
    GunInfos gun_infos;
    BulletInfos bullet_infos;
    EntityInfoTables(const CharacterInfos& character, const GunInfos& guns, const BulletInfos& bullets):
        character_infos(character), gun_infos(guns), bullet_infos(bullets) {}
};