#pragma once
#include <vector>

#include "../../element/Element.hpp"
#include "../../model/polygon/Rectangle.hpp"
#include "../../Quadtree/QuadtreeTypeDefs/QuadtreeEl.hpp"

class Location final : public Identifiable{
    std::vector<Element*> _missed_blocks;
    Rectangle _rectangle;
    bool _is_used_blocks = false;
public:
    Location(Rectangle &&rectangle, const size_t id);

    void addMissedBlock(Element* element);
    void excludeMissingBlocks(QuadtreeEl& quadtree_el);
    void integrateMissingBlocks(QuadtreeEl& quadtree_el);
    const std::vector<Element*>& getMissedBlocks();
    [[nodiscard]] const Polygon& getPolygon() const;

    ~Location() noexcept override;
    
    Location(Location&&) noexcept = default;
    Location& operator=(Location&&) noexcept = default;
    
    Location(const Location&) = delete;
    Location& operator=(const Location&) = delete;
};
