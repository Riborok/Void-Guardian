#pragma once
#include "CharacterLimits.hpp"
#include "choose character/ChooseCharacterController.hpp"
#include "GameInfo.hpp"
#include "GameMaster.hpp"
#include "GameState.hpp"
#include "../GameSetup.hpp"

class GameStarter final {
    GameSetup *_game_setup;
    PauseSubset _pause_subset;
    GameInfo _game_info;
    ChooseCharacterController _choose_character_controller;

    AnimatedSprites createAnimatedSprites(const CharacterLimits &character_limits);
    void setLvlTitle() const;
public:
    GameStarter(GameSetup& game_setup, PauseController &pause_controller, GameInfo &&game_info, const std::string& src,
        const Colors &choose_colors, const CharacterLimits &character_limits);
    [[nodiscard]] GameState startGame();
    
    ~GameStarter() noexcept = default;
    GameStarter(GameStarter&&) noexcept = delete;
    GameStarter& operator=(GameStarter&&) noexcept = delete;
    GameStarter(const GameStarter&) noexcept = delete;
    GameStarter& operator=(const GameStarter&) noexcept = delete;
};
