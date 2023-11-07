#include "../../../include/game/construction/MapCreation.hpp"

#include "../../../include/additionally/Constants.hpp"
#include "../../../include/game/construction/BoundaryCreation.hpp"
#include "../../../include/game/construction/LocationCreation.hpp"

namespace MapCreation {
    namespace InnerLogic {
        bool isLeft(const DoorOpening door_opening) { return static_cast<int>(door_opening) & static_cast<int>(DoorOpening::LEFT); }
        bool isRight(const DoorOpening door_opening) { return static_cast<int>(door_opening) & static_cast<int>(DoorOpening::RIGHT); }
        bool isTop(const DoorOpening door_opening) { return static_cast<int>(door_opening) & static_cast<int>(DoorOpening::TOP); }
        bool isBottom(const DoorOpening door_opening) { return static_cast<int>(door_opening) & static_cast<int>(DoorOpening::BOTTOM); }

        sf::Vector2u getDelta(const sf::Vector2u &size, const sf::Vector2f &scale) {
            return {
                static_cast<unsigned>(static_cast<float>(size.x) * scale.x),
                static_cast<unsigned>(static_cast<float>(size.y) * scale.y)
            };
        }
    }

    DoorOpening operator|(DoorOpening operand1, DoorOpening operand2) {
        return static_cast<DoorOpening>(static_cast<int>(operand1) | static_cast<int>(operand2));
    }
    
    void createBackground(const int num, const sf::Vector2u &p0, const sf::Vector2u &p1,
        Quadtree<Element> &quadtree, const sf::Vector2f &scale) {
        const auto delta = InnerLogic::getDelta(Constants::BACKGROUND_SIZE, scale);
        
        unsigned y = p0.y;
        while (y < p1.y) {
            unsigned x = p0.x;
            while (x < p1.x) {
                quadtree.insert(ElementCreation::create({static_cast<float>(x), static_cast<float>(y)},
                    0, Types::ElementTypes::BACKGROUND, num, scale));
                x += delta.x;
            }
            y += delta.y;
        }
    }
    
    void createBackground(const int num, const sf::Vector2u &p0, const unsigned count_x, const unsigned count_y,
         Quadtree<Element> &quadtree, const sf::Vector2f &scale) {
        const auto delta = InnerLogic::getDelta(Constants::BACKGROUND_SIZE, scale);
        const sf::Vector2u p1(p0.x + delta.x * count_x,p0.y + delta.y * count_y);
        createBackground(num, p0, p1, quadtree, scale);
    }
    
    Location *createLocation(const int num, const sf::Vector2u &p0, const sf::Vector2u &p1,
        const sf::Vector2f &scale, const DoorOpening door_opening,
        Quadtree<Element> &quadtree,
        const unsigned offset_x, const unsigned offset_y) {
        const sf::Vector2u delta = InnerLogic::getDelta(Constants::BLOCK_SIZE, scale);
        const unsigned start_x = p0.x + delta.x;
        const unsigned start_y = p0.y + delta.y;
        const unsigned last_x = p1.x - delta.x;
        const unsigned last_y = p1.y - delta.y;

        const auto location = LocationCreation::create(start_x, start_y, last_x, last_y);

        BoundaryCreation::createHorBoundary(num, p0, p1.x, quadtree, location, scale, delta.x,
            InnerLogic::isTop(door_opening) ? offset_x : 0);
        BoundaryCreation::createHorBoundary(num, {p0.x, last_y}, p1.x, quadtree, location, scale, delta.x,
            InnerLogic::isBottom(door_opening) ? offset_x : 0);

        BoundaryCreation::createVertBoundary(num, {p0.x, start_y}, last_y, quadtree, location, scale, delta.y,
            InnerLogic::isLeft(door_opening) ? offset_y : 0);
        BoundaryCreation::createVertBoundary(num, {last_x, start_y}, last_y, quadtree, location, scale, delta.y,
            InnerLogic::isRight(door_opening) ? offset_y : 0);
        return location;
    }
    
    Location *createLocation(const int num, const sf::Vector2u &p0, const unsigned count_x, const unsigned count_y,
        const sf::Vector2f &scale, const DoorOpening door_opening,
        Quadtree<Element> &quadtree,
        const unsigned amount_offset_x, const unsigned amount_offset_y) {
        const auto delta = InnerLogic::getDelta(Constants::BLOCK_SIZE, scale);
        const sf::Vector2u p1(p0.x + delta.x * count_x, p0.y + delta.y * count_y);
        return createLocation(num, p0, p1, scale, door_opening, quadtree,
            amount_offset_x * delta.x, amount_offset_y * delta.y);
    }
}
