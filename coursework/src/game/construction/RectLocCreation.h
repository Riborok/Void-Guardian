#pragma once
#include "RectLoc.h"

namespace RectLocCreation {
    inline RectLoc *create(const unsigned x0, const unsigned y0, const unsigned x1, const unsigned y1) {
        return new RectLoc(
            new Rectangle(static_cast<float>(x0), static_cast<float>(y0),
                static_cast<float>(x1), static_cast<float>(y1)),
            Constants::id_tracker.generate(Types::RECT_LOC));
    }
}