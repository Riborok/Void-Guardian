#pragma once
#include <vector>

#include "../../element/Element.hpp"
#include "../../model/polygon/Rectangle.hpp"

class Location final : public Identifiable{
    std::vector<Element*> _missed_blocks;
    Polygon *_polygon;
    bool _is_used_blocks = false;
public:
    explicit Location(Polygon* polygon, const size_t id);

    void addBlock(Element* element);
    const std::vector<Element*>& getMissedBlocks(const bool is_used_blocks);
    [[nodiscard]] Polygon& getPolygon() const;

    ~Location() noexcept override;
    
    Location(Location&&) = default;
    Location& operator=(Location&&) = default;
    
    Location(const Location&) = delete;
    Location& operator=(const Location&) = delete;
};