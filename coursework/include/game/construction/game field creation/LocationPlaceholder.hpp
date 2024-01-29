#pragma once

#include "LocationMap.hpp"
#include "../../entity/component/gun/GunInstaller.hpp"
#include "arena/ArenaCreator.hpp"
#include "portal/PortalCreator.hpp"

namespace LocationPlaceholder {
    void fillRooms(const LocationMap &location_map, GunInstaller &gun_installer, const PortalCreator &portal_creator,
        const ArenaCreator &arena_creator, const size_t lvl);
}