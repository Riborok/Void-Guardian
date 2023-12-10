#include "include/game/GameData.hpp"
#include "include/game/GameMaster.hpp"

void main() {
    auto *window = new sf::RenderWindow();
    auto *game_master = new GameMaster(*window, GameData(
        
        SimpleSpriteInfos{
            {ElementType::BACKGROUND, {{{"./img/backgrounds/Background_", 0}}}},
            {ElementType::BULLET, {{{"./img/bullets/Bullet_", 4}}}},
            {ElementType::BLOCK, {{{"./img/blocks/Block_", 1}}, {4, 10}}},
            {ElementType::GUN, {{{"./img/guns/Gun_", 2}}}},
        },
        AnimatedSpriteInfos{
            {ElementType::PORTAL,
                    {{
                        {16, 70, "./img/portal/Portal_", 1}
                    }}
                },
            {ElementType::WRAITH,
                {{
                    {12, 40, "./img/wraiths/Wraith_", 3},
                   {12, 40, "./img/wraiths/Wraith_walking_", 3}
                }}
            },
            {ElementType::WRAITH_DYING,
                {{
                    {15, 40, "./img/wraiths/Wraith_dying_", 5}
                }}
            },
            {ElementType::BULLET_IMPACT,
                {{
                    {4, 60, "./img/bullets/Bullet_impact_", 5}
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
        {{{-0.47f, -0.47f}, {1.0f, 1.0f}, 0},
            {{-0.47f, -0.47f}, {1.0f, 1.0f}, 1}},
        {1, 1},
        
        "Void Guardian",
        "./img/Icon.png",
        
        WraithInfos{
            EntityData{WraithStats{0.6f}, EntityInfo{100, 100, 1}, {0.3f, 0.3f}},
        },
        GunInfos{
            EntityPartData{GunInfo{720, {1.0f, 1.0f, 1.0f}}, {2.0f, 2.0f}},
            EntityPartData{GunInfo{820, {1.2f, 1.1f, 1.1f}}, {2.0f, 2.0f}},
            EntityPartData{GunInfo{620, {1.05f, 1.05f, 1.05f}}, {2.0f, 2.0f}},
            EntityPartData{GunInfo{1000, {1.35f, 1.35f, 1.35f}}, {2.0f, 2.0f}},
            EntityPartData{GunInfo{700, {1.2f, 0.95f, 1.0f}}, {2.0f, 2.0f}},
            EntityPartData{GunInfo{500, {1.0f, 1.1f, 1.0f}}, {2.0f, 2.0f}},
            EntityPartData{GunInfo{1000, {1.5f, 1.25f, 1.25f}}, {2.0f, 2.0f}},
            EntityPartData{GunInfo{850, {1.35f, 1.2f, 1.0f}}, {2.0f, 2.0f}},
            EntityPartData{GunInfo{350, {0.8f, 0.8f, 0.8f}}, {2.0f, 2.0f}},
            EntityPartData{GunInfo{400, {0.9f, 0.9f, 0.9f}}, {2.0f, 2.0f}},
            EntityPartData{GunInfo{550, {1.2f, 1.2f, 1.2f}}, {2.0f, 2.0f}},
            EntityPartData{GunInfo{600, {1.35f, 1.35f, 1.35f}}, {2.0f, 2.0f}},
            EntityPartData{GunInfo{500, {1.5f, 1.5f, 1.5f}}, {2.0f, 2.0f}},
            EntityPartData{GunInfo{350, {1.0f, 1.0f, 1.0f}}, {2.0f, 2.0f}},
            EntityPartData{GunInfo{300, {0.9f, 0.9f, 0.9f}}, {2.0f, 2.0f}},
            EntityPartData{GunInfo{1500, {2.0f, 2.0f, 2.0f}}, {2.0f, 2.0f}},  
        },
        BulletInfos{
            EntityData{BulletInfo{10, 0.05f, 3.0f}, EntityInfo{1, 1, 1}, {1.25f, 1.25f}},
            EntityData{BulletInfo{12, 0.12f, 3.2f}, EntityInfo{1, 1, 1}, {1.25f, 1.25f}},
            EntityData{BulletInfo{15, 0.15f, 3.0f}, EntityInfo{1, 1, 1}, {1.25f, 1.25f}},
            EntityData{BulletInfo{12, 0.2f, 3.0f}, EntityInfo{1, 1, 1}, {1.25f, 1.25f}},
            EntityData{BulletInfo{15, 0.1f, 3.0f}, EntityInfo{1, 1, 1}, {1.25f, 1.25f}},
            EntityData{BulletInfo{17, 0.2f, 3.0f}, EntityInfo{1, 1, 1}, {1.25f, 1.25f}},
            EntityData{BulletInfo{8, 0.2f, 4.0f}, EntityInfo{1, 1, 1}, {1.25f, 1.25f}},
            EntityData{BulletInfo{5, 0.2f, 4.2f}, EntityInfo{1, 1, 1}, {1.25f, 1.25f}},
            EntityData{BulletInfo{6, 0.2f, 4.2f}, EntityInfo{1, 1, 1}, {1.25f, 1.25f}},
            EntityData{BulletInfo{10, 0.3f, 3.0f}, EntityInfo{1, 1, 1}, {1.25f, 1.25f}},
            EntityData{BulletInfo{12, 0.2f, 3.2f}, EntityInfo{1, 1, 1}, {1.25f, 1.25f}},
            EntityData{BulletInfo{8, 0.2f, 4.0f}, EntityInfo{1, 1, 1}, {1.25f, 1.25f}},
            EntityData{BulletInfo{12, 0.08f, 5.0f}, EntityInfo{1, 1, 1}, {1.25f, 1.25f}},
            EntityData{BulletInfo{10, 0.1f, 3.0f}, EntityInfo{1, 1, 1}, {1.25f, 1.25f}},
            EntityData{BulletInfo{9, 0.1f, 4.5f}, EntityInfo{1, 1, 1}, {1.25f, 1.25f}},
            EntityData{BulletInfo{13, 0.2f, 4.0f}, EntityInfo{1, 1, 1}, {1.25f, 1.25f}},
        }
    ));
    
    game_master->start();

    delete window;
    delete game_master;
}