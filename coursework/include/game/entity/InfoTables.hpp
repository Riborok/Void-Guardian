#pragma once
#include <array>

#include "EntitiesInfo.hpp"
#include "bullet/BulletStats.hpp"
#include "component/character/CharacterStats.hpp"
#include "component/gun/GunStats.hpp"

constexpr size_t CHARACTER_COUNT = 6;
constexpr size_t GUN_COUNT = 16;
constexpr size_t BULLET_COUNT = GUN_COUNT;

typedef FightingEntitiesInfo<CharacterStats> CharacterInfo;
typedef EntitiesPartInfo<GunStats> GunInfo;
typedef EntitiesInfo<BulletStats> BulletInfo;

typedef std::array<CharacterInfo, CHARACTER_COUNT> CharacterInfos;
typedef std::array<GunInfo, GUN_COUNT> GunInfos;
typedef std::array<BulletInfo, BULLET_COUNT> BulletInfos;

struct EntityInfoTables final {
    CharacterInfos character_infos;
    GunInfos gun_infos;
    BulletInfos bullet_infos;
    EntityInfoTables(const CharacterInfos& character, const GunInfos& guns, const BulletInfos& bullets):
        character_infos(character), gun_infos(guns), bullet_infos(bullets) {}
};