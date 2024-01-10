#include "../../include/additionally/LevelParameters.hpp"
#include "../../include/geometry/Trigonometry.hpp"

float getExponent(const size_t lvl) {
    if (lvl < LevelParameters::FIRST_THRESHOLD)
        return static_cast<float>(LevelParameters::FIRST_THRESHOLD - lvl);

    if (lvl < LevelParameters::SECOND_THRESHOLD)
        return 1 / static_cast<float>(2 + lvl - LevelParameters::FIRST_THRESHOLD);    

    return 1 / static_cast<float>(2 + LevelParameters::SECOND_THRESHOLD - LevelParameters::FIRST_THRESHOLD);
}

ExponentGenerator LevelParameters::createGunNumGenerator(const size_t lvl) {
    static constexpr int START_GUN_NUM = 1;
    static constexpr int END_GUN_NUM = 15;
    
    return {START_GUN_NUM, END_GUN_NUM, getExponent(lvl)};
}

ExponentGenerator LevelParameters::createEnemyCharacterNumGenerator(const size_t lvl) {
    static constexpr int START_ENEMY_CHARACTER_NUM = 3;
    static constexpr int END_ENEMY_CHARACTER_NUM = 5;
    
    return {START_ENEMY_CHARACTER_NUM, END_ENEMY_CHARACTER_NUM, getExponent(lvl)};
}

size_t LevelParameters::getBackgroundNum(const size_t lvl) {
    static constexpr size_t START_BACKGROUND_NUM = 0;
    
    if (lvl < FIRST_THRESHOLD)
        return START_BACKGROUND_NUM;

    if (lvl < SECOND_THRESHOLD)
        return START_BACKGROUND_NUM + 1;    

    return START_BACKGROUND_NUM + 2;
}

size_t LevelParameters::getBoundaryNum(const size_t lvl) {
    static constexpr size_t START_BOUNDARY_NUM = 0;
    
    if (lvl < FIRST_THRESHOLD)
        return lvl < FIRST_THRESHOLD / 2 ? START_BOUNDARY_NUM : START_BOUNDARY_NUM + 1;

    if (lvl < SECOND_THRESHOLD)
        return START_BOUNDARY_NUM + 2;    

    return START_BOUNDARY_NUM + 3;
}

EnemySpawnConfiguration LevelParameters::getEnemySpawnConfiguration(const size_t lvl) {
    static constexpr size_t BASE_ENEMIES = 3;
    static constexpr int BASE_SPAWN_INTERVAL = 5000;
    
    if (lvl < FIRST_THRESHOLD) 
        return {BASE_ENEMIES + lvl, BASE_SPAWN_INTERVAL - static_cast<int>(lvl) * 100};
    
    if (lvl < SECOND_THRESHOLD) 
        return {BASE_ENEMIES + lvl * 2, BASE_SPAWN_INTERVAL - static_cast<int>(lvl) * 200};

    return {BASE_ENEMIES + SECOND_THRESHOLD * 2, BASE_SPAWN_INTERVAL - SECOND_THRESHOLD * 250};
}

RandomSize LevelParameters::getArenaRandomSize(const size_t lvl) {
    static constexpr int BASE_START_SIZE_X = 16;
    static constexpr int BASE_START_SIZE_Y = 12;
    static constexpr int BASE_SIZE_OFFSET = 4;
    
    int start_x;
    int start_y;
    int offset;
    if (lvl < FIRST_THRESHOLD) {
        start_x = BASE_START_SIZE_X + static_cast<int>(lvl);
        start_y = BASE_START_SIZE_Y + static_cast<int>(lvl);
        offset = BASE_SIZE_OFFSET;
    }
    else if (lvl < SECOND_THRESHOLD) {
        start_x = BASE_START_SIZE_X + static_cast<int>(lvl) * 2;
        start_y = BASE_START_SIZE_Y + static_cast<int>(lvl) * 2;
        offset = BASE_SIZE_OFFSET * 2;
    }
    else {
        start_x = BASE_START_SIZE_X + SECOND_THRESHOLD * 2;
        start_y = BASE_START_SIZE_Y + SECOND_THRESHOLD * 2;
        offset = BASE_SIZE_OFFSET * 3;
    }
    return {std::uniform_int_distribution<int>{start_x, start_x + offset},
    std::uniform_int_distribution<int>{start_y, start_y + offset}};
}

std::uniform_real_distribution<float> LevelParameters::getBulletSpread(const size_t lvl) {
    static constexpr float BASE_SPREAD = 0.6f;

    float spread;
    if (lvl < FIRST_THRESHOLD) 
        spread = BASE_SPREAD - static_cast<float>(lvl) * Trigonometry::EPSILON_RADIANS * 1.82f;
    else if (lvl < SECOND_THRESHOLD) 
        spread = BASE_SPREAD - static_cast<float>(lvl) * Trigonometry::EPSILON_RADIANS * 2.5f;
    else
        spread = BASE_SPREAD - SECOND_THRESHOLD * Trigonometry::EPSILON_RADIANS * 2.82f;     
    
    return std::uniform_real_distribution<float>{-spread, spread};
}