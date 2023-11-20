#include "../../../include/game/construction/Location.hpp"

#include <stdexcept>

Location::Location(Rectangle &&rectangle, const size_t id) : Identifiable(id), _rectangle(std::move(rectangle)) {}

void Location::addMissedBlock(Element* element) {
    _missed_blocks.push_back(element);
}

void Location::excludeMissingBlocks(QuadtreeEl& quadtree_el) {
    _is_used_blocks = false;
    for (const auto* block : _missed_blocks)
        if (!quadtree_el.remove(block))
            throw std::runtime_error("Failed to remove missed block into the quadtree.");
}

void Location::integrateMissingBlocks(QuadtreeEl& quadtree_el) {
    _is_used_blocks = true;
    for (const auto* block : _missed_blocks)
        if (!quadtree_el.insert(block))
            throw std::runtime_error("Failed to insert missed block into the quadtree.");
}

const std::vector<Element*>& Location::getMissedBlocks() { return _missed_blocks; }

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