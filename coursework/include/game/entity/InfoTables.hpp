#pragma once
#include <array>

#include "EntityInfo.hpp"
#include "bullet/BulletInfo.hpp"
#include "component/character/CharacterStats.hpp"
#include "component/gun/GunInfo.hpp"

constexpr size_t WRAITH_COUNT = 3;
constexpr size_t GUN_COUNT = 16;
constexpr size_t BULLET_COUNT = GUN_COUNT;

typedef std::array<EntityData<CharacterStats>, WRAITH_COUNT> WraithInfos;
typedef std::array<EntityPartData<GunInfo>, GUN_COUNT> GunInfos;

typedef std::array<EntityData<BulletInfo>, BULLET_COUNT> BulletInfos;