#include "../../../include/game/construction/Location.hpp"

Location::Location(Rectangle &&rectangle, const size_t id) : Identifiable(id), _rectangle(std::move(rectangle)) {}

void Location::addMissedBlock(Element* element) {
    _missed_blocks.push_back(element);
}

const std::vector<Element*>& Location::getMissedBlocks(const bool is_used_blocks) {
    _is_used_blocks = is_used_blocks;
    return _missed_blocks;
}

const Polygon& Location::getPolygon() const {
    return _rectangle;
}

Location::~Location() noexcept {
    if (!_is_used_blocks) {
        for (const auto* block : _missed_blocks) {
            delete block;
        }
    }
}