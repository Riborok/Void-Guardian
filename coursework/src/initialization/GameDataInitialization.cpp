#include "../../include/initialization/GameDataInitialization.hpp"

inline SimpleSpriteInfos initializeSimpleSpriteInfos() {
    return {
        {ElementType::BACKGROUND, {{{"./AppData/img/backgrounds/Background_", 0}}}},
        {ElementType::BULLET, {{{"./AppData/img/bullets/Bullet_", 4}}}},
        {ElementType::BLOCK, {{{"./AppData/img/blocks/Block_", 1}}, {4, 10}}},
        {ElementType::GUN, {{{"./AppData/img/guns/Gun_", 2}}}},
    };
}

inline AnimatedSpriteInfos initializeAnimatedSpriteInfos() {
    return {
        {ElementType::PORTAL, {{{FrameInfoContainer{{{{16, 70}, 2}}},
            "./AppData/img/portal/Portal_", 1}}}},
        {ElementType::CHARACTER,{{
            {FrameInfoContainer{{{{12, 40}, 2}, {{18, 40}, 3}}},
                "./AppData/img/characters/Character_", 3},
            {FrameInfoContainer{{{{12, 40}, 2}, {{12, 65}, 3}}},
                "./AppData/img/characters/Character_walking_", 3}
        }}},
    {ElementType::BULLET_IMPACT, {{{FrameInfoContainer{{{{4, 60}, 15}}},
        "./AppData/img/bullets/Bullet_impact_", 5}}, {0, 5}}},
    {ElementType::CHARACTER_DYING, {{{FrameInfoContainer{{{{15, 40}, 3}}},
        "./AppData/img/wraiths/Wraith_dying_", 5}}}},
    };
}

inline CollisionTable initializeCollisionTable() {
    return {
        CollisionTable::AvailableCollisions{ElementType::BLOCK},
        {
            {ElementType::BLOCK, new CollisionTable::AvailableCollisions{
                ElementType::BLOCK, ElementType::CHARACTER}
            },
            {ElementType::CHARACTER, new CollisionTable::AvailableCollisions{
                ElementType::BLOCK, ElementType::CHARACTER}
            },
            {ElementType::GUN, new CollisionTable::AvailableCollisions{
                ElementType::BLOCK}
            },
            {ElementType::BULLET, new CollisionTable::AvailableCollisions{
                ElementType::BLOCK, ElementType::CHARACTER, ElementType::BULLET}
            }
        }
    };
}

inline BuildingData initializeBuildingData() {
    return {
        BackgroundData{{128, 128}, {0.75, 0.75}},
        BoundaryData{{128, 128}, {0.75, 0.75}, {4, 4}}
    };
}

inline InOutPortals initializeInOutPortals() {
    return {
        {{-0.47f, -0.47f}, {1.0f, 1.0f}, 0},
        {{-0.47f, -0.47f}, {1.0f, 1.0f}, 1}
    };
}

inline CharacterInfos initializeCharacterInfos() {
    return {
        EntityData{CharacterStats{0.6f}, EntityInfo{100, 100, 1}, {0.3f, 0.3f}},
        EntityData{CharacterStats{0.4f}, EntityInfo{120, 120, 1.15f}, {0.3f, 0.3f}},
        EntityData{CharacterStats{0.8f}, EntityInfo{80, 80, 0.85f}, {0.3f, 0.3f}},
        EntityData{CharacterStats{0.3f}, EntityInfo{50, 50, 1}, {0.16f, 0.16f}}
    };
}

inline GunInfos initializeGunInfos() {
    return {
        /* 0 */  EntityPartData{GunInfo{750, {7, 19}}, {2.0f, 2.0f}},
        /* 1 */  EntityPartData{GunInfo{800, {7, 19}}, {2.0f, 2.0f}},
        /* 2 */  EntityPartData{GunInfo{600, {7, 19}}, {2.0f, 2.0f}},
        /* 3 */  EntityPartData{GunInfo{1200, {6, 19.5f}}, {2.0f, 2.0f}},
        /* 4 */  EntityPartData{GunInfo{800, {7, 19.5f}}, {1.85f, 1.85f}},
        /* 5 */  EntityPartData{GunInfo{600, {6.5f, 19}}, {2.0f, 2.0f}},
        /* 6 */  EntityPartData{GunInfo{1000, {2, 12}}, {1.6f, 1.6f}},
        /* 7 */  EntityPartData{GunInfo{850, {3, 12}}, {1.5f, 1.5f}},
        /* 8 */  EntityPartData{GunInfo{350, {-1, 18}}, {2.0f, 2.0f}},
        /* 9 */  EntityPartData{GunInfo{400, {-1, 14}}, {2.0f, 2.0f}},
        /* 10 */ EntityPartData{GunInfo{750, {-1, 17}}, {1.8f, 1.8f}},
        /* 11 */ EntityPartData{GunInfo{600, {-5, 15}}, {1.8f, 1.8f}},
        /* 12 */ EntityPartData{GunInfo{500, {-2, 7}}, {1.6f, 1.6f}},
        /* 13 */ EntityPartData{GunInfo{350, {-1, 7}}, {1.8f, 1.8f}},
        /* 14 */ EntityPartData{GunInfo{300, {-2, 11}}, {1.6f, 1.6f}},
        /* 15 */ EntityPartData{GunInfo{1500, {-8, 8}}, {1.8f, 1.8f}},  
    };
}

inline BulletInfos initializeBulletInfos() {
    return {
        /* 0 */  EntityData{BulletInfo{8, 0.05f, 3.0f},
            EntityInfo{1, 1, 1}, {1.25f, 1.25f}},
        /* 1 */  EntityData{BulletInfo{10, 0.15f, 3.2f},
                    EntityInfo{3, 3, 1}, {1.25f, 1.25f}},
        /* 2 */  EntityData{BulletInfo{7, 0.075f, 2.9f},
                    EntityInfo{5, 3, 1}, {1.25f, 1.25f}},
        /* 3 */  EntityData{BulletInfo{19, 0.225f, 2.7f},
                    EntityInfo{5, 5, 1}, {1.25f, 1.25f}},
        /* 4 */  EntityData{BulletInfo{14, 0.125f, 3.0f},
                    EntityInfo{7, 7, 1}, {1.25f, 1.25f}},
        /* 5 */  EntityData{BulletInfo{10, 0.05f, 3.0f},
                    EntityInfo{10, 10, 1}, {1.25f, 1.25f}},
        /* 6 */  EntityData{BulletInfo{23, 0.3f, 4.0f},
                    EntityInfo{5, 5, 1}, {1.25f, 1.25f}},
        /* 7 */  EntityData{BulletInfo{20, 0.2f, 4.2f},
                    EntityInfo{6, 7, 1}, {1.25f, 1.25f}},
        /* 8 */  EntityData{BulletInfo{12, 0.1f, 4.2f},
                    EntityInfo{8, 8, 1}, {1.25f, 1.25f}},
        /* 9 */  EntityData{BulletInfo{10, 0.15f, 3.0f},
                    EntityInfo{2, 2, 1}, {1.25f, 1.25f}},
        /* 10 */ EntityData{BulletInfo{22, 0.3f, 3.2f},
                    EntityInfo{8, 10, 1}, {1.25f, 1.25f}},
        /* 11 */ EntityData{BulletInfo{20, 0.35f, 4.0f},
                    EntityInfo{4, 4, 1}, {1.25f, 1.25f}},
        /* 12 */ EntityData{BulletInfo{19, 0.2f, 5.0f},
                    EntityInfo{2, 3, 1}, {1.25f, 1.25f}},
        /* 13 */ EntityData{BulletInfo{18, 0.2f, 3.0f},
                    EntityInfo{15, 17, 1}, {1.25f, 1.25f}},
        /* 14 */ EntityData{BulletInfo{19, 0.175f, 3.5f},
                    EntityInfo{13, 15, 1}, {1.25f, 1.25f}},
        /* 15 */ EntityData{BulletInfo{32, 0.425f, 4.2f},
                    EntityInfo{12, 12, 1}, {1.25f, 1.25f}},
    };
}

GameData GameDataInitialization::initializeGameData() {
    return {
        initializeSimpleSpriteInfos(),
        initializeAnimatedSpriteInfos(),
        initializeCollisionTable(),
        initializeBuildingData(),
        initializeInOutPortals(),
        {
            initializeCharacterInfos(),
            initializeGunInfos(),
            initializeBulletInfos()
        },
    };
}

WindowInfo GameDataInitialization::initializeWindowInfo() {
    return {"Void Guardian", "./AppData/img/Icon.png"};
}