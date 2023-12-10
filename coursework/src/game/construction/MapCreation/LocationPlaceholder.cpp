#include "../../../../include/game/construction/MapCreation/LocationPlaceholder.hpp"

#include "../../../../include/game/identifiable/LocationIdTracker.hpp"

class GunNumGenerator final {
    mutable std::uniform_real_distribution<float> _distribution{0.0f, 1.0f};
public:
    int generate() const {
        const float random_value = 1.0f - AdditionalFunc::getRandom(_distribution);
        return static_cast<int>(std::round(1 + 14 * random_value * random_value));
    }
    
    GunNumGenerator() noexcept = default;
    ~GunNumGenerator() noexcept = default;
    GunNumGenerator(GunNumGenerator&&) noexcept = delete;
    GunNumGenerator& operator=(GunNumGenerator&&) noexcept = delete;
    GunNumGenerator(const GunNumGenerator&) noexcept = delete;
    GunNumGenerator& operator=(const GunNumGenerator&) noexcept = delete;
};

void LocationPlaceholder::fillRooms(const LocationMap &location_map, ElementCreator &element_creator,
        GameField &game_field, const InOutPortals &portals_data) {
    const GunNumGenerator gun_num_generator;
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
            game_field.gun_manager.createGun(room->getPolygon().calcCenter(), gun_num_generator.generate());
            break;
        case RoomType::BATTLE:

            break;
        }
    }
}
