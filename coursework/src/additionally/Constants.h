#pragma once
#include <string>
#include <vector>

#include "Types.h"

namespace Constants {
    const std::string TITLE = "Void Guardian";
    const std::string ICON_SRC = "./img/Icon.png";

    const sf::Vector2u BACKGROUND_SIZE(128, 128);
    const sf::Vector2u BLOCK_SIZE(128, 128);
    
    const Types::SimpleSpriteInfo SIMPLE_SPRITE_INFO[] {
        {std::vector<std::string>{"./img/backgrounds/Background_"}, 0},
        {std::vector<std::string>{"./img/blocks/Block_"}, 1},
        {std::vector<std::string>{"./img/guns/Gun_"}, 3},
    };
        
    const Types::AnimatedSpriteInfo ANIMATED_SPRITE_INFO[] {
        {
            std::vector<std::string>{"./img/wraiths/Wraith_", "./img/wraiths/Wraith_walking_"},
            12, 40, 2
        },
        {
            std::vector<std::string>{"./img/wraiths/Wraith_dying_"},
            15, 40, 4
        }
    };
}
