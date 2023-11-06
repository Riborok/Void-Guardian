#pragma once
#include <vector>

#include "../../element/Element.h"
#include "../../model/polygon/Rectangle.h"

class RectLoc final : public Identifiable{
    std::vector<Element*> _missed_blocks;
    Rectangle *_rectangle;
    bool _is_used_blocks = false;
public:
    explicit RectLoc(Rectangle *rectangle, const size_t id) : Identifiable(id), _rectangle(rectangle) { }
    void addBlock(Element *element) { _missed_blocks.push_back(element); }
    
    const std::vector<Element*> &getMissedBlocks(const bool is_used_blocks) {
        _is_used_blocks = is_used_blocks;
        return _missed_blocks;
    }
    Polygon &getPolygon() const { return *_rectangle; }

    ~RectLoc() noexcept override {
        delete _rectangle;
        if (!_is_used_blocks)
            for (const auto *block : _missed_blocks)
                delete block;
    }
    RectLoc(RectLoc&&) = default;
    RectLoc& operator=(RectLoc&&) = default;
    
    RectLoc(const RectLoc&) = delete;
    RectLoc& operator=(const RectLoc&) = delete;
};