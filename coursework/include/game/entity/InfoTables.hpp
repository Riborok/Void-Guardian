﻿#pragma once
#include <array>

#include "EntitiesData.hpp"
#include "bullet/BulletInfo.hpp"
#include "component/character/CharacterStats.hpp"
#include "component/gun/GunInfo.hpp"

constexpr size_t CHARACTER_COUNT = 6;
constexpr size_t GUN_COUNT = 16;
constexpr size_t BULLET_COUNT = GUN_COUNT;

typedef FightingEntitiesData<CharacterStats> CharacterData;
typedef EntitiesPartData<GunInfo> GunData;
typedef EntitiesData<BulletInfo> BulletData;

typedef std::array<CharacterData, CHARACTER_COUNT> CharacterInfos;
typedef std::array<GunData, GUN_COUNT> GunInfos;
typedef std::array<BulletData, BULLET_COUNT> BulletInfos;

struct EntityInfoTables final {
    CharacterInfos character_infos;
    GunInfos gun_infos;
    BulletInfos bullet_infos;
    EntityInfoTables(const CharacterInfos& character, const GunInfos& guns, const BulletInfos& bullets):
        character_infos(character), gun_infos(guns), bullet_infos(bullets) {}
};