#include "include/game/GameData.hpp"
#include "include/game/GameMaster.hpp"

void main() {
    auto *window = new sf::RenderWindow();
    auto *game_master = new GameMaster(*window, GameData(
        
        SimpleSpriteInfos{
            {ElementType::BACKGROUND, {{{"./img/backgrounds/Background_", 0}}}},
            {ElementType::GUN, {{{"./img/guns/Gun_", 3}}}},
            {ElementType::BULLET, {{{"./img/bullets/Bullet_", 3}}}},
            {ElementType::BLOCK, {{{"./img/blocks/Block_", 1}}, {4, 10}}}
        },
        AnimatedSpriteInfos{
            {ElementType::WRAITH,
                {{
                    {12, 40, "./img/wraiths/Wraith_", 2},
                   {12, 40, "./img/wraiths/Wraith_walking_", 2}
                }}
            },
            {ElementType::WRAITH_DYING,
                {{
                    {15, 40, "./img/wraiths/Wraith_dying_", 4}
                }}
            },
            {ElementType::BULLET_IMPACT,
                {{
                    {4, 60, "./img/bullets/Bullet_impact_", 4}
                }, {0, 5}}
            }
        },
        
        CollisionTable{
            {ElementType::BLOCK, new CollisionTable::AvailableCollisions{
                ElementType::BLOCK, ElementType::WRAITH}
            },
            {ElementType::WRAITH, new CollisionTable::AvailableCollisions{
                ElementType::BLOCK, ElementType::WRAITH}
            },
            {ElementType::BULLET, new CollisionTable::AvailableCollisions{
                ElementType::BLOCK, ElementType::WRAITH, ElementType::BULLET}
            }
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
            EntityPartData{GunInfo{720, {1, 1, 1}}, {2.0f, 2.0f}},
        },
        BulletInfos{
            EntityData{BulletInfo{10, 0.1, 3}, EntityInfo{1, 1, 1}, {1.25f, 1.25f}},
        }
    ));
    
    game_master->start();

    delete window;
    delete game_master;
}
