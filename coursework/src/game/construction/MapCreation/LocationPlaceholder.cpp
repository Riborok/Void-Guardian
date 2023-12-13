#include "../../../../include/game/construction/MapCreation/LocationPlaceholder.hpp"

#include "../../../../include/additionally/ExponentGenerator.hpp"
#include "../../../../include/game/entity/player/gun/GunManager.hpp"
#include "../../../../include/game/identifiable/LocationIdTracker.hpp"

void LocationPlaceholder::fillRooms(const LocationMap &location_map, ElementCreator &element_creator,
        GunManager &gun_manager, GameField &game_field, const InOutPortals &portals_data, const size_t lvl) {
    const ExponentGenerator gun_num_generator(createGunNumGenerator(lvl));
    for (const auto& room : location_map.getItemSequence()) {
        switch (LocationIdTracker::extractType(room->getId())) {
        case RoomType::SPAWN: {
            const auto& portal_data = portals_data.in_portal;
            game_field.quadtree_el.insert(element_creator.create({
                room->getPolygon().calcCenter(), 0, ElementType::PORTAL, portal_data.num, portal_data.scale
            }, portal_data.portal_offset));    
            break;
        }
        case RoomType::PORTAL: {
            const auto& portal_data = portals_data.out_portal;
            game_field.quadtree_el.insert(element_creator.create({
                room->getPolygon().calcCenter(), 0, ElementType::PORTAL, portal_data.num, portal_data.scale
            }, portal_data.portal_offset));
            break;
        }
        case RoomType::BOX:
            gun_manager.createGun(room->getPolygon().calcCenter(), gun_num_generator.generate());
            break;
        case RoomType::BATTLE:

            break;
        }
    }
}
