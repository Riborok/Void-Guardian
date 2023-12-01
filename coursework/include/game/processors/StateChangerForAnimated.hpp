#pragma once
#include "../../geometry/collision/ElementCollisionSet.hpp"

class StateChangerForAnimated final {
    StateChangerForAnimated() {}
public:
    static void change(const ElementCollisionSet &element_collision_set, const int delta_time);
};