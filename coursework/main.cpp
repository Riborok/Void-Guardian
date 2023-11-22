#include "include/game/GameMaster.hpp"

void main() {
    sf::RenderWindow window;
    
    auto *game_master = new GameMaster(window, GameData(
        SimpleSpriteInfos{
            SimpleSpriteInfo{StringVector{"./img/backgrounds/Background_"}, 0},
            SimpleSpriteInfo{StringVector{"./img/blocks/Block_"}, 1},
            SimpleSpriteInfo{StringVector{"./img/guns/Gun_"}, 3}
        },
        AnimatedSpriteInfos{
            AnimatedSpriteInfo{StringVector{"./img/wraiths/Wraith_", "./img/wraiths/Wraith_walking_"},
                12, 40, 2},
            AnimatedSpriteInfo{StringVector{"./img/wraiths/Wraith_dying_"},
                15, 40, 4}
        },
        BuildingData(0, {128, 128}, {0.75, 0.75}),
        LocationBuildingData(0, {128, 128}, {0.75, 0.75}, {4, 4}),
        "Void Guardian",
        "./img/Icon.png",
        PlayerInfo({0.3f, 0.3f}, 1.2f),
        sf::Vector2i(2, 2))
    );
    game_master->start();
    delete game_master;
}
