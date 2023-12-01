#include <stdexcept>

#include "../../../include/game/identifiable/ElementIdTracker.hpp"

ElementType ElementIdTracker::extractType(const size_t id) {
    return static_cast<ElementType>(id % TYPE_DIGITS_DIVIDER);
}

bool ElementIdTracker::isAnimated(const size_t id) {
    const auto type = extractType(id);
    return type >= ANIMATED_TYPES_START && type <= ANIMATED_TYPES_END;
}

bool ElementIdTracker::isAnimation(const size_t id) {
    const auto type = extractType(id);
    return type >= ANIMATION_TYPES_START && type <= ANIMATION_TYPES_END;
}

size_t ElementIdTracker::generate(const ElementType type) {
    return generate(toSizeT(type));
}

size_t ElementIdTracker::generate(const size_t type) {
    return _ids[type] == MAX_VALUE
        ? throw std::runtime_error("Maximum ID is reached.")
        : _ids[type]++ * TYPE_DIGITS_DIVIDER + type;
}