// ReSharper disable CppClangTidyClangDiagnosticCoveredSwitchDefault
#include "../../../include/game/construction/DoorOpening.hpp"

#include "../../../include/additionally/AdditionalFunc.hpp"

const std::array<DoorOpening, TOTAL_DIRECTIONS> DOOR_OPENINGS {
    DoorOpening::LEFT, DoorOpening::RIGHT, DoorOpening::TOP, DoorOpening::BOTTOM
};

DoorOpening getOppositeDoor(const DoorOpening door_opening) {
    switch (door_opening) {
    case DoorOpening::LEFT      :   return DoorOpening::RIGHT;
    case DoorOpening::RIGHT     :   return DoorOpening::LEFT;
    case DoorOpening::TOP       :   return DoorOpening::BOTTOM;
    case DoorOpening::BOTTOM    :   return DoorOpening::TOP;
    case DoorOpening::NONE      :
    default                     :   throw std::invalid_argument("Invalid DoorOpening type");
    }
}

sf::Vector2i movePosition(const DoorOpening door_opening, const sf::Vector2i &pos) {
    switch (door_opening) {
    case DoorOpening::LEFT      :   return {pos.x - 1, pos.y};
    case DoorOpening::RIGHT     :   return {pos.x + 1, pos.y};
    case DoorOpening::TOP       :   return {pos.x, pos.y - 1};
    case DoorOpening::BOTTOM    :   return {pos.x, pos.y + 1};
    case DoorOpening::NONE      :
    default                     :   throw std::invalid_argument("Invalid DoorOpening type");
    }
}

bool isVert(const DoorOpening door_opening) {
    switch (door_opening) {
    case DoorOpening::LEFT      :
    case DoorOpening::RIGHT     :   return false;
    case DoorOpening::TOP       :
    case DoorOpening::BOTTOM    :   return true;
    case DoorOpening::NONE      :
    default                     :   throw std::invalid_argument("Invalid DoorOpening type");
    }
}