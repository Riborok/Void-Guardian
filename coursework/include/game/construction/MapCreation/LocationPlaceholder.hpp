#pragma once

#include "LocationMap.hpp"
#include "PortalData.hpp"
#include "../../GameField.hpp"
#include "../../../element/ElementCreator.hpp"

namespace LocationPlaceholder {
    void fillRooms(const LocationMap &location_map, ElementCreator &element_creator,
        GameField &game_field, const InOutPortals &portals_data);
}