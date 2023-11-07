#include "../../../include/game/construction/Location.hpp"

Location::Location(Polygon* polygon, const size_t id) : Identifiable(id), _polygon(polygon) {}

void Location::addBlock(Element* element) {
    _missed_blocks.push_back(element);
}

const std::vector<Element*>& Location::getMissedBlocks(const bool is_used_blocks) {
    _is_used_blocks = is_used_blocks;
    return _missed_blocks;
}

Polygon& Location::getPolygon() const {
    return *_polygon;
}

Location::~Location() noexcept {
    delete _polygon;
    if (!_is_used_blocks) {
        for (const auto* block : _missed_blocks) {
            delete block;
        }
    }
}