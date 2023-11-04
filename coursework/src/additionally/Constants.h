#pragma once
#include <string>
#include <utility>
#include <vector>

namespace Constants {
    const std::string TITLE = "Void Guardian";
    const std::string ICON_SRC = "./img/Icon.png";
    
    const std::pair<std::vector<std::string>, int> SIMPLE_SPRITE_INFO[] {
        std::make_pair(std::vector<std::string>{"./img/backgrounds/Background_"}, 0),
        std::make_pair(std::vector<std::string>{"./img/blocks/Block_"}, 1),
        std::make_pair(std::vector<std::string>{"./img/guns/Gun_"}, 3),
    };
    const sf::Vector2u BACKGROUND_SIZE(128, 128);
    const sf::Vector2u BLOCK_SIZE(128, 128);
        
    const std::pair<std::pair<std::vector<std::string>, int>, std::pair<int, int>> ANIMATED_SPRITE_INFO[] {
        std::make_pair(std::make_pair(std::vector<std::string>{"./img/wraiths/Wraith_", "./img/wraiths/Wraith_walking_"}, 12), std::make_pair(40, 2)),
        std::make_pair(std::make_pair(std::vector<std::string>{"./img/wraiths/Wraith_dying_"}, 15), std::make_pair(40, 4)),
    };
}
