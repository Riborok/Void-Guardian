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
    void excludeMissingBlocks(QuadtreeEl& quadtree_el) noexcept(false);
    void integrateMissingBlocks(QuadtreeEl& quadtree_el) noexcept(false);
    const Elements& getMissedBlocks();
    [[nodiscard]] const Polygon& getPolygon() const;

    ~Location() noexcept override;
    
    Location(Location&&) noexcept = delete;
    Location& operator=(Location&&) noexcept = delete;
    
    Location(const Location&) noexcept = delete;
    Location& operator=(const Location&) noexcept = delete;
};
