#pragma once

#include "LocationMap.hpp"
#include "PortalData.hpp"
#include "../../GameField.hpp"
#include "../../../element/ElementCreator.hpp"
#include "../../entity/player/gun/GunManager.hpp"

namespace LocationPlaceholder {
    void fillRooms(const LocationMap &location_map, ElementCreator &element_creator,
        GunManager &gun_manager, GameField &game_field, const InOutPortals &portals_data);
}