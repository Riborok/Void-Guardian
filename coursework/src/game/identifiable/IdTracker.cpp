#include <stdexcept>

#include "../../../include/game/identifiable/IdTracker.hpp"

ElementTypes IdTracker::extractType(const size_t id) {
    return static_cast<ElementTypes>(id % TYPE_DIGITS_DIVIDER);
}

bool IdTracker::isAnimated(const size_t id) {
    return extractType(id) >= ANIMATED_TYPES_START;
}

bool IdTracker::isAnimation(const size_t id) {
    return extractType(id) >= ANIMATION_TYPES_START;
}

size_t IdTracker::generate(const ElementTypes type) {
    return generate(static_cast<size_t>(type));
}

size_t IdTracker::generate(const size_t type) {
    const size_t id = ++_ids[type];

    if (id >= MAX_VALUE)
        throw std::runtime_error("Maximum ID is reached.");
    return id * TYPE_DIGITS_DIVIDER + static_cast<size_t>(type);
}