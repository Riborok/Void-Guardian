#include "include/game/GameMaster.hpp"

void main() {
    auto *window = new sf::RenderWindow();
    auto *game_master = new GameMaster(*window, GameData(
        SimpleSpriteInfos{
            SimpleSpriteInfo{{"./img/backgrounds/Background_"}, 0},
            SimpleSpriteInfo{{"./img/blocks/Block_"}, 1},
            SimpleSpriteInfo{{"./img/guns/Gun_"}, 3}
        },
        AnimatedSpriteInfos{
            AnimatedSpriteInfo{{"./img/wraiths/Wraith_", "./img/wraiths/Wraith_walking_"},
                12, 40, 2},
            AnimatedSpriteInfo{{"./img/wraiths/Wraith_dying_"},
                15, 40, 4}
        },
        {0, {128, 128}, {0.75, 0.75}},
        {0, {128, 128}, {0.75, 0.75}, {4, 4}},
        "Void Guardian",
        "./img/Icon.png",
        PlayerInfo({0.3f, 0.3f}, 1.2f),
        {2, 2})
    );
    
    game_master->start();

    delete window;
    delete game_master;
}
