#include "../../../include/game/game handlers/StateChangerForAnimated.hpp"

#include "../../../include/game/identifiable/ElementIdTracker.hpp"
#include "../../../include/sprite/AnimatedSprite.hpp"

void StateChangerForAnimated::change(const ElementCollisionSet &element_collision_set, const int delta_time) {
    for (const auto* element : element_collision_set) {
        if (const size_t id = element->getId(); ElementIdTracker::isAnimated(id)) {
            auto* animated_sprite = static_cast<AnimatedSprite*>(element->_sprite); // NOLINT(cppcoreguidelines-pro-type-static-cast-downcast)
            animated_sprite->changeState(delta_time);
        }
    }
}
