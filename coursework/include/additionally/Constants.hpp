#pragma once
#include <string>

#include "Types.hpp"
#include "../game/identifiable/IdTracker.hpp"

namespace Constants {
    extern IdTracker id_tracker;
    extern const std::string TITLE;
    extern const std::string ICON_SRC;
    extern const sf::Vector2u BACKGROUND_SIZE;
    extern const sf::Vector2u BLOCK_SIZE;
    extern const Types::SimpleSpriteInfo SIMPLE_SPRITE_INFO[];
    extern const Types::AnimatedSpriteInfo ANIMATED_SPRITE_INFO[];
}
