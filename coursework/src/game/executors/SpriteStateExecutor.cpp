#include "../../../include/game/executors/SpriteStateExecutor.hpp"

#include "../../../include/game/identifiable/ElementIdTracker.hpp"
#include "../../../include/sprite/AnimatedSprite.hpp"

SpriteStateExecutor::SpriteStateExecutor(GameUpdater &game_updater)
    : _game_updater(&game_updater) {}

void SpriteStateExecutor::handle(const int delta_time) {
    std::vector<const Element*> elements_to_delete;

    for (const auto* element : _game_updater->getElements()) {
        if (const size_t id = element->getId(); ElementIdTracker::isAnimated(id)) {
            auto* animated_sprite = static_cast<AnimatedSprite*>(element->_sprite); // NOLINT(cppcoreguidelines-pro-type-static-cast-downcast)
            animated_sprite->changeState(delta_time);
            if (ElementIdTracker::isAnimation(id) && animated_sprite->isAnimationRestarted())
                elements_to_delete.push_back(element);
        }
    }
    for (const auto* element : elements_to_delete)
        _game_updater->removeElement(element);
}