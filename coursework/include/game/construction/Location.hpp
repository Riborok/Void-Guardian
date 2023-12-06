#pragma once

#include "../../element/Element.hpp"
#include "../../model/rectangle/Rectangle.hpp"
#include "../../quadtree/quadtree type defs/QuadtreeEl.hpp"

class Location final : public Identifiable{
    Elements _missed_blocks;
    Rectangle _rectangle;
    bool _is_used_blocks = false;
public:
    Location(Rectangle &&rectangle, const size_t id);

    void addMissedBlock(const Element* element);
    void excludeMissingBlocks(QuadtreeEl& quadtree_el);
    void integrateMissingBlocks(QuadtreeEl& quadtree_el);
    const Elements& getMissedBlocks();
    [[nodiscard]] const Polygon& getPolygon() const;

    ~Location() noexcept override;
    
    Location(Location&&) noexcept = default;
    Location& operator=(Location&&) noexcept = default;
    
    Location(const Location&) = delete;
    Location& operator=(const Location&) = delete;
};
