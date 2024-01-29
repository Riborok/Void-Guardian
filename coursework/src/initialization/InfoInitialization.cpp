#include "..\..\include\initialization\InfoInitialization.hpp"

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

inline BuildingParameters initializeBuildingParameters() {
    return {
        BackgroundParameters{{128, 128}, {0.75, 0.75}},
        BoundaryParameters{{128, 128}, {0.75, 0.75}, {4, 4}}
    };
}

inline InOutPortalInfo initializeInOutPortals() {
    return {
        {{-0.47f, -0.47f}, {1.0f, 1.0f}, 0},
        {{-0.47f, -0.47f}, {1.0f, 1.0f}, 1}
    };
}

inline CharacterInfos initializeCharacterInfos() {
    return {
        FightingEntitiesInfo{CharacterStats{0.6f}, EntityInfo{100, 30, 1.15f}, {0, 0}, {0.3f, 0.3f}},
        FightingEntitiesInfo{CharacterStats{0.4f}, EntityInfo{120, 40, 1.3f}, {0, 0}, {0.3f, 0.3f}},
        FightingEntitiesInfo{CharacterStats{0.8f}, EntityInfo{90, 20, 1}, {0, 0}, {0.3f, 0.3f}},
        FightingEntitiesInfo{CharacterStats{0.3f}, EntityInfo{40, 10, 0.15f}, {0, 0}, {0.16f, 0.16f}},
        FightingEntitiesInfo{CharacterStats{0.4f}, EntityInfo{55, 20, 0.45f}, {0, 0}, {0.16f, 0.16f}},
        FightingEntitiesInfo{CharacterStats{0.5f}, EntityInfo{70, 30, 0.8f}, {0, 0}, {0.16f, 0.16f}}
    };
}

inline GunInfos initializeGunInfos() {
    return {
        /* 0 */  EntitiesPartInfo{GunStats{750, {7, 19}}, {2.0f, 2.0f}},
        /* 1 */  EntitiesPartInfo{GunStats{800, {7, 19}}, {2.0f, 2.0f}},
        /* 2 */  EntitiesPartInfo{GunStats{600, {7, 19}}, {2.0f, 2.0f}},
        /* 3 */  EntitiesPartInfo{GunStats{1200, {6, 19.5f}}, {2.0f, 2.0f}},
        /* 4 */  EntitiesPartInfo{GunStats{800, {7, 19.5f}}, {1.85f, 1.85f}},
        /* 5 */  EntitiesPartInfo{GunStats{600, {6.5f, 19}}, {2.0f, 2.0f}},
        /* 6 */  EntitiesPartInfo{GunStats{1000, {2, 12}}, {1.6f, 1.6f}},
        /* 7 */  EntitiesPartInfo{GunStats{850, {3, 12}}, {1.5f, 1.5f}},
        /* 8 */  EntitiesPartInfo{GunStats{350, {-1, 18}}, {2.0f, 2.0f}},
        /* 9 */  EntitiesPartInfo{GunStats{400, {-1, 14}}, {2.0f, 2.0f}},
        /* 10 */ EntitiesPartInfo{GunStats{750, {-1, 17}}, {1.8f, 1.8f}},
        /* 11 */ EntitiesPartInfo{GunStats{600, {-5, 15}}, {1.8f, 1.8f}},
        /* 12 */ EntitiesPartInfo{GunStats{250, {-2, 7}}, {1.6f, 1.6f}},
        /* 13 */ EntitiesPartInfo{GunStats{550, {-1, 7}}, {1.8f, 1.8f}},
        /* 14 */ EntitiesPartInfo{GunStats{450, {-2, 11}}, {1.6f, 1.6f}},
        /* 15 */ EntitiesPartInfo{GunStats{1500, {-8, 8}}, {1.8f, 1.8f}},  
    };
}

inline BulletInfos initializeBulletInfos() {
    return {
        /* 0 */  EntitiesInfo{BulletStats{8, 0.05f, 3.0f},
            EntityInfo{1, 1, 1}, {1.25f, 1.25f}},
        /* 1 */  EntitiesInfo{BulletStats{11, 0.05f, 3.2f},
                    EntityInfo{3, 3, 0.15f}, {1.25f, 1.25f}},
        /* 2 */  EntitiesInfo{BulletStats{9, 0.075f, 2.9f},
                    EntityInfo{5, 3, 0.15f}, {1.25f, 1.25f}},
        /* 3 */  EntitiesInfo{BulletStats{19, 0.1f, 2.7f},
                    EntityInfo{5, 5, 0.15f}, {1.25f, 1.25f}},
        /* 4 */  EntitiesInfo{BulletStats{13, 0.075f, 3.0f},
                    EntityInfo{7, 7, 0.15f}, {1.25f, 1.25f}},
        /* 5 */  EntitiesInfo{BulletStats{12, 0.05f, 3.0f},
                    EntityInfo{10, 10, 0.15f}, {1.25f, 1.25f}},
        /* 6 */  EntitiesInfo{BulletStats{23, 0.125f, 4.0f},
                    EntityInfo{5, 5, 0.15f}, {1.25f, 1.25f}},
        /* 7 */  EntitiesInfo{BulletStats{20, 0.1f, 4.2f},
                    EntityInfo{6, 7, 0.15f}, {1.25f, 1.25f}},
        /* 8 */  EntitiesInfo{BulletStats{13, 0.075f, 4.2f},
                    EntityInfo{8, 8, 0.15f}, {1.25f, 1.25f}},
        /* 9 */  EntitiesInfo{BulletStats{13, 0.125f, 3.0f},
                    EntityInfo{2, 2, 0.15f}, {1.25f, 1.25f}},
        /* 10 */ EntitiesInfo{BulletStats{22, 0.2f, 3.2f},
                    EntityInfo{8, 10, 0.15f}, {1.25f, 1.25f}},
        /* 11 */ EntitiesInfo{BulletStats{20, 0.25f, 4.0f},
                    EntityInfo{4, 4, 0.15f}, {1.25f, 1.25f}},
        /* 12 */ EntitiesInfo{BulletStats{16, 0.1f, 5.0f},
                    EntityInfo{2, 3, 0.15f}, {1.25f, 1.25f}},
        /* 13 */ EntitiesInfo{BulletStats{23, 0.2f, 2.75f},
                    EntityInfo{15, 17, 0.15f}, {1.25f, 1.25f}},
        /* 14 */ EntitiesInfo{BulletStats{25, 0.225f, 3.25f},
                    EntityInfo{13, 15, 0.15f}, {1.25f, 1.25f}},
        /* 15 */ EntitiesInfo{BulletStats{32, 0.3f, 4.2f},
                    EntityInfo{12, 12, 0.15f}, {1.25f, 1.25f}},
    };
}

inline std::string initializeHealthFontSrc() {
    return "./AppData/font/arial.ttf";
}

inline std::string initializeFontSrc() {
    return "./AppData/font/BebasNeue Bold.ttf";
}

inline LoadingScreenInfo::Strings initializeLoadingStrings() {
    return {"Loading .", "Loading ..", "Loading ..."};
}

inline SettingColors initializeSettingColors() {
    return {InfoInitialization::initializeColors(), {110, 110, 10}};
}

GameInfo InfoInitialization::initializeGameInfo() {
    return {
        initializeSimpleSpriteInfos(),
        initializeAnimatedSpriteInfos(),
        initializeCollisionTable(),
        initializeBuildingParameters(),
        initializeInOutPortals(),
        {
            initializeCharacterInfos(),
            initializeGunInfos(),
            initializeBulletInfos()
        },
        initializeHealthFontSrc(),
    };
}

WindowInfo InfoInitialization::initializeWindowInfo() {
    return {"Void Guardian", "./AppData/img/Icon.png"};
}

std::string InfoInitialization::initializeAimCursorSrc() {
    return "./AppData/img/Aim.png";
}

UIController InfoInitialization::initializeUIController(GameContext& game_context) {
    auto* font = new sf::Font();
    font->loadFromFile(initializeFontSrc());
    auto* cursors = new Cursors();
    return {game_context, initializeSettingColors(), font, cursors, initializeLoadingStrings()};
}

Colors InfoInitialization::initializeColors() {
    return {sf::Color::Black, sf::Color::White, sf::Color::Yellow};
}

std::string InfoInitialization::initializeAboutUrl() {
    return "https://github.com/Riborok";
}

CharacterLimits InfoInitialization::initializeCharacterLimits() {
    return {0, 2};
}