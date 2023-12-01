﻿#pragma once
#include <array>

#include "EntityInfo.hpp"
#include "bullet/BulletInfo.hpp"
#include "player/gun/GunInfo.hpp"
#include "player/wraith/WraithStats.hpp"

constexpr size_t WRAITH_COUNT = 1;
constexpr size_t GUN_COUNT = 1;
constexpr size_t BULLET_COUNT = GUN_COUNT;

typedef std::array<const EntityData<WraithStats>, WRAITH_COUNT> WraithInfos;
typedef std::array<const EntityPartData<GunInfo>, GUN_COUNT> GunInfos;

typedef std::array<const EntityData<BulletInfo>, BULLET_COUNT> BulletInfos;