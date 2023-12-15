#pragma once

#include "LocationMap.hpp"
#include "../../entity/player/gun/GunManager.hpp"
#include "portal/PortalCreator.hpp"

namespace LocationPlaceholder {
    void fillRooms(const LocationMap &location_map, GunManager &gun_manager, const PortalCreator &portal_creator,
        const size_t lvl);
}