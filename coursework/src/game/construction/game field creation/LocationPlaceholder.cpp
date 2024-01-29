#include "../../../../include/game/construction/game field creation/LocationPlaceholder.hpp"

#include "../../../../include/additionally/LevelParameters.hpp"
#include "../../../../include/game/entity/component/gun/GunInstaller.hpp"
#include "../../../../include/game/identifiable/LocationIdTracker.hpp"

void LocationPlaceholder::fillRooms(const LocationMap &location_map, GunInstaller &gun_installer,
        const PortalCreator &portal_creator, const ArenaCreator &arena_creator, const size_t lvl) {
    const ExponentGenerator gun_num_generator(LevelParameters::createGunNumGenerator(lvl));
    for (const auto* room : location_map.getItemSequence()) {
        switch (LocationIdTracker::extractType(room->getId())) {
        case RoomType::SPAWN: {
            portal_creator.createInPortal(room->getPolygon().calcCenter(), 0);  
            break;
        }
        case RoomType::PORTAL: {
            portal_creator.createOutPortal(room->getPolygon().calcCenter(), 0);
            break;
        }
        case RoomType::BOX:
            gun_installer.createGun(room->getPolygon().calcCenter(), gun_num_generator.generate());
            break;
        case RoomType::ARENA:
            arena_creator.create(*room);
            break;
        }
    }
}
