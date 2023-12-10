#include <stdexcept>
#include "../../../include/game/identifiable/LocationIdTracker.hpp"

RoomType LocationIdTracker::extractType(const size_t id) {
    return static_cast<RoomType>(id % TYPE_DIGITS_DIVIDER);
}

size_t LocationIdTracker::generate(const RoomType type) {
    return generate(static_cast<size_t>(type));
}

size_t LocationIdTracker::generate(const size_t type) {
    return _ids[type] == MAX_VALUE
    ? throw std::runtime_error("Maximum ID is reached.")
    : _ids[type]++ * TYPE_DIGITS_DIVIDER + type;
}
