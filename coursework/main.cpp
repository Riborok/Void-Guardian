#include "include/additionally/other types/PlayerInfo.hpp"
#include "include/game/GameMaster.hpp"

void main() {
    auto *window = new sf::RenderWindow();
    auto *game_master = new GameMaster(*window, GameData(
        SimpleSpriteInfos{
            {ElementType::BACKGROUND, SimpleSpriteInfo{{"./img/backgrounds/Background_", 0}}},
            {ElementType::GUN, SimpleSpriteInfo{{"./img/guns/Gun_", 3}}},
            {ElementType::BLOCK, SimpleSpriteInfo{{"./img/blocks/Block_", 1}}}
        },
        AnimatedSpriteInfos{
            {ElementType::WRAITH,
                AnimatedSpriteInfo{
                    {12, 40, "./img/wraiths/Wraith_", 2},
                   {12, 40, "./img/wraiths/Wraith_walking_", 2}
                }
            },
            {ElementType::WRAITH_DYING,
                AnimatedSpriteInfo{
                    {15, 40, "./img/wraiths/Wraith_dying_", 4}
                }
            }
        },
        {
            {ElementType::BLOCK, new AvailableCollisions{ElementType::BLOCK, ElementType::WRAITH}},
            {ElementType::WRAITH, new AvailableCollisions{ElementType::BLOCK, ElementType::WRAITH}}
        },
        {0, {128, 128}, {0.75, 0.75}},
        {0, {128, 128}, {0.75, 0.75}, {4, 4}},
        {2, 2},
        "Void Guardian",
        "./img/Icon.png",
        {{0.3f, 0.3f}, 1.2f}
    ));
    
    game_master->start();

    delete window;
    delete game_master;
}
