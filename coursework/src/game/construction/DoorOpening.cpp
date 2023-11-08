// ReSharper disable CppClangTidyClangDiagnosticCoveredSwitchDefault
#include "../../../include/game/construction/DoorOpening.hpp"

#include "../../../include/additionally/AdditionalFunc.hpp"

size_t getSerialNumber(const DoorOpening door_opening) {
    switch (door_opening) {
        case DoorOpening::LEFT      :   return 0;
        case DoorOpening::RIGHT     :   return 1;
        case DoorOpening::TOP       :   return 2;
        case DoorOpening::BOTTOM    :   return 3;
        case DoorOpening::NONE      :
        default                     :   throw std::invalid_argument("Invalid DoorOpening type");
    }
}

const std::array<DoorOpening, AMOUNT_OF_DIRECTIONS> DOOR_OPENINGS {
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