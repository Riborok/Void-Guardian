#pragma once
#include <array>

#include "EntityInfo.hpp"
#include "bullet/BulletInfo.hpp"
#include "player/gun/GunInfo.hpp"
#include "player/wraith/WraithInfo.hpp"

constexpr size_t WRAITH_COUNT = 1;
constexpr size_t GUN_COUNT = 1;
constexpr size_t BULLET_COUNT = GUN_COUNT;

typedef std::array<EntityData<WraithInfo>, WRAITH_COUNT> WraithInfos;
typedef std::array<EntityPartData<GunInfo>, GUN_COUNT> GunInfos;

typedef std::array<EntityData<BulletInfo>, BULLET_COUNT> BulletInfos;