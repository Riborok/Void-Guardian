#pragma once
#include "CharacterLimits.hpp"
#include "ChooseCharacterManager.hpp"
#include "GameData.hpp"
#include "GameMaster.hpp"
#include "GameState.hpp"
#include "../GameSetup.hpp"

class GameManager final {
    GameSetup *_game_setup;
    PauseSubset _pause_subset;
    GameData _game_data;
    ChooseCharacterManager _choose_character_manager;

    AnimatedSprites createAnimatedSprites(const CharacterLimits &character_limits);
    void setLvlTitle() const;
public:
    GameManager(GameSetup& game_setup, PauseManager &pause_manager, GameData &&game_data, const std::string& src,
        const Colors &choose_colors, const CharacterLimits &character_limits);
    [[nodiscard]] GameState startGame();
    
    ~GameManager() noexcept = default;
    GameManager(GameManager&&) noexcept = delete;
    GameManager& operator=(GameManager&&) noexcept = delete;
    GameManager(const GameManager&) noexcept = delete;
    GameManager& operator=(const GameManager&) noexcept = delete;
};
