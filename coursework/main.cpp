#include "include/game/GameData.hpp"
#include "include/game/GameMaster.hpp"

void main() {
    auto *window = new sf::RenderWindow();
    auto *game_master = new GameMaster(*window, GameData(
        
        SimpleSpriteInfos{
            {ElementType::BACKGROUND, SimpleSpriteInfo{{"./img/backgrounds/Background_", 0}}},
            {ElementType::GUN, SimpleSpriteInfo{{"./img/guns/Gun_", 3}}},
            {ElementType::BULLET, SimpleSpriteInfo{{"./img/bullets/Bullet_", 3}}},
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
        
        CollisionTable{
            {ElementType::BLOCK, new AvailableCollisions{ElementType::BLOCK, ElementType::WRAITH}},
            {ElementType::WRAITH, new AvailableCollisions{ElementType::BLOCK, ElementType::WRAITH}},
            {ElementType::BULLET, new AvailableCollisions{ElementType::BLOCK, ElementType::WRAITH, ElementType::BULLET}}
        },
        
        {0, {128, 128}, {0.75, 0.75}},
        {0, {128, 128}, {0.75, 0.75}, {4, 4}},
        {2, 2},
        
        "Void Guardian",
        "./img/Icon.png",
        
        WraithInfos{
            EntityData{WraithStats{0.6}, EntityInfo{100, 100, 1}, {0.3f, 0.3f}},
        },
        GunInfos{
            EntityPartData{GunInfo{100, {1, 1, 1}}, {2.0f, 2.0f}},
        },
        BulletInfos{
            EntityData{BulletInfo{10, 0.1, 3}, EntityInfo{1, 1, 1}, {0.3f, 0.3f}},
        }
    ));
    
    game_master->start();

    delete window;
    delete game_master;
}
