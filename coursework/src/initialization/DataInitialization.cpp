﻿#include "../../include/initialization/DataInitialization.hpp"

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
            {FrameInfoContainer{{{{12, 40}, 2}, {{18, 40}, 6}}},
                "./AppData/img/characters/Character_", 3},
            {FrameInfoContainer{{{{12, 40}, 2}, {{12, 65}, 6}}},
                "./AppData/img/characters/Character_walking_", 3}
        }, {3, 6}}},
    {ElementType::BULLET_IMPACT, {{{FrameInfoContainer{{{{4, 60}, 15}}},
        "./AppData/img/bullets/Bullet_impact_", 5}}, {0, 5}}},
    {ElementType::CHARACTER_DYING, {{{FrameInfoContainer{{{{15, 40}, 6}}},
        "./AppData/img/characters/Character_dying_", 5}}, {3, 6}}},
    };
}

inline CollisionTable initializeCollisionTable() {
    return {
        CollisionTable::AvailableCollisions{ElementType::CHARACTER, ElementType::BLOCK},
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
        FightingEntitiesData{CharacterStats{0.6f}, EntityInfo{100, 30, 1.15f}, {0, 0}, {0.3f, 0.3f}},
        FightingEntitiesData{CharacterStats{0.4f}, EntityInfo{120, 40, 1.3f}, {0, 0}, {0.3f, 0.3f}},
        FightingEntitiesData{CharacterStats{0.8f}, EntityInfo{90, 20, 1}, {0, 0}, {0.3f, 0.3f}},
        FightingEntitiesData{CharacterStats{0.3f}, EntityInfo{40, 10, 0.15f}, {0, 0}, {0.16f, 0.16f}},
        FightingEntitiesData{CharacterStats{0.4f}, EntityInfo{55, 20, 0.15f}, {0, 0}, {0.16f, 0.16f}},
        FightingEntitiesData{CharacterStats{0.5f}, EntityInfo{70, 25, 0.15f}, {0, 0}, {0.16f, 0.16f}}
    };
}

inline GunInfos initializeGunInfos() {
    return {
        /* 0 */  EntitiesPartData{GunInfo{750, {7, 19}}, {2.0f, 2.0f}},
        /* 1 */  EntitiesPartData{GunInfo{800, {7, 19}}, {2.0f, 2.0f}},
        /* 2 */  EntitiesPartData{GunInfo{600, {7, 19}}, {2.0f, 2.0f}},
        /* 3 */  EntitiesPartData{GunInfo{1200, {6, 19.5f}}, {2.0f, 2.0f}},
        /* 4 */  EntitiesPartData{GunInfo{800, {7, 19.5f}}, {1.85f, 1.85f}},
        /* 5 */  EntitiesPartData{GunInfo{600, {6.5f, 19}}, {2.0f, 2.0f}},
        /* 6 */  EntitiesPartData{GunInfo{1000, {2, 12}}, {1.6f, 1.6f}},
        /* 7 */  EntitiesPartData{GunInfo{850, {3, 12}}, {1.5f, 1.5f}},
        /* 8 */  EntitiesPartData{GunInfo{350, {-1, 18}}, {2.0f, 2.0f}},
        /* 9 */  EntitiesPartData{GunInfo{400, {-1, 14}}, {2.0f, 2.0f}},
        /* 10 */ EntitiesPartData{GunInfo{750, {-1, 17}}, {1.8f, 1.8f}},
        /* 11 */ EntitiesPartData{GunInfo{600, {-5, 15}}, {1.8f, 1.8f}},
        /* 12 */ EntitiesPartData{GunInfo{500, {-2, 7}}, {1.6f, 1.6f}},
        /* 13 */ EntitiesPartData{GunInfo{350, {-1, 7}}, {1.8f, 1.8f}},
        /* 14 */ EntitiesPartData{GunInfo{300, {-2, 11}}, {1.6f, 1.6f}},
        /* 15 */ EntitiesPartData{GunInfo{1500, {-8, 8}}, {1.8f, 1.8f}},  
    };
}

inline BulletInfos initializeBulletInfos() {
    return {
        /* 0 */  EntitiesData{BulletInfo{8, 0.05f, 3.0f},
            EntityInfo{1, 1, 1}, {1.25f, 1.25f}},
        /* 1 */  EntitiesData{BulletInfo{10, 0.15f, 3.2f},
                    EntityInfo{3, 3, 1}, {1.25f, 1.25f}},
        /* 2 */  EntitiesData{BulletInfo{7, 0.075f, 2.9f},
                    EntityInfo{5, 3, 1}, {1.25f, 1.25f}},
        /* 3 */  EntitiesData{BulletInfo{19, 0.225f, 2.7f},
                    EntityInfo{5, 5, 1}, {1.25f, 1.25f}},
        /* 4 */  EntitiesData{BulletInfo{14, 0.125f, 3.0f},
                    EntityInfo{7, 7, 1}, {1.25f, 1.25f}},
        /* 5 */  EntitiesData{BulletInfo{10, 0.05f, 3.0f},
                    EntityInfo{10, 10, 1}, {1.25f, 1.25f}},
        /* 6 */  EntitiesData{BulletInfo{23, 0.3f, 4.0f},
                    EntityInfo{5, 5, 1}, {1.25f, 1.25f}},
        /* 7 */  EntitiesData{BulletInfo{20, 0.2f, 4.2f},
                    EntityInfo{6, 7, 1}, {1.25f, 1.25f}},
        /* 8 */  EntitiesData{BulletInfo{12, 0.1f, 4.2f},
                    EntityInfo{8, 8, 1}, {1.25f, 1.25f}},
        /* 9 */  EntitiesData{BulletInfo{10, 0.15f, 3.0f},
                    EntityInfo{2, 2, 1}, {1.25f, 1.25f}},
        /* 10 */ EntitiesData{BulletInfo{22, 0.3f, 3.2f},
                    EntityInfo{8, 10, 1}, {1.25f, 1.25f}},
        /* 11 */ EntitiesData{BulletInfo{20, 0.35f, 4.0f},
                    EntityInfo{4, 4, 1}, {1.25f, 1.25f}},
        /* 12 */ EntitiesData{BulletInfo{19, 0.2f, 5.0f},
                    EntityInfo{2, 3, 1}, {1.25f, 1.25f}},
        /* 13 */ EntitiesData{BulletInfo{18, 0.2f, 3.0f},
                    EntityInfo{15, 17, 1}, {1.25f, 1.25f}},
        /* 14 */ EntitiesData{BulletInfo{19, 0.175f, 3.5f},
                    EntityInfo{13, 15, 1}, {1.25f, 1.25f}},
        /* 15 */ EntitiesData{BulletInfo{32, 0.425f, 4.2f},
                    EntityInfo{12, 12, 1}, {1.25f, 1.25f}},
    };
}

inline std::string initializeHealthFontSrc() {
    return "./AppData/font/arial.ttf";
}

inline std::string initializeFontSrc() {
    return "./AppData/font/BebasNeue Bold.ttf";
}

inline LoadingScreenInfo initializeLoadingScreenInfo(const sf::Font &font) {
    return {font, {"Loading .", "Loading ..", "Loading ..."}};
}

inline SettingsManagerInfo initializeSettingsManagerInfo(const sf::Font &font) {
    return SettingsManagerInfo{font};
}

inline SettingColors initializeSettingColors() {
    return {DataInitialization::initializeColors(), {110, 110, 10}};
}

GameData DataInitialization::initializeGameData() {
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
        initializeHealthFontSrc(),
    };
}

WindowInfo DataInitialization::initializeWindowInfo() {
    return {"Void Guardian", "./AppData/img/Icon.png"};
}

std::string DataInitialization::initializeAimCursorSrc() {
    return "./AppData/img/Aim.png";
}

GUIManager DataInitialization::initializeGUIManagers(GameContext& game_context) {
    auto* font = new sf::Font(); font->loadFromFile(initializeFontSrc());
    auto* cursors = new Cursors();
    return {game_context, initializeSettingColors(), font, cursors,
        initializeLoadingScreenInfo(*font), initializeSettingsManagerInfo(*font)};
}

Colors DataInitialization::initializeColors() {
    return {sf::Color::Black, sf::Color::White, sf::Color::Yellow};
}

std::string DataInitialization::initializeAboutUrl() {
    return "https://github.com/Riborok";
}