#pragma once
#include "CharacterVisualization.hpp"
#include "../GameState.hpp"
#include "../../GameContext.hpp"
#include "../../gui/Buttons.hpp"
#include "../../gui/Cursors.hpp"
#include "../game handlers/game loop/GameLoopState.hpp"

class ChooseCharacterController final {
    static constexpr size_t WAIT_DELAY = 12;
    static constexpr float BUTTON_SPACING = 80.0f;
    static constexpr float BUTTON_X_INDENT = 20;
    static constexpr float Y_START_FACTOR = 2.7f;
    
    GameContext *_game_context;
    CharacterVisualization _character_visualization;
    Buttons _buttons;
    const Cursors *_cursors;
    sf::Color _background_color;
    GameState *_game_state = nullptr;
    GameLoopState _game_loop_state;
    
    [[nodiscard]] size_t& getSpriteIndex() const;

    void setPositions();
    void createButtons(const ButtonColors& button_colors);
    void draw(const int delta_time);
    void handleKeyPressed(const sf::Keyboard::Key key);
    void handleEvents();
public:
    ChooseCharacterController(GameContext &game_context, AnimatedSprites &&sprites, CharacterInfos &character_infos,
        const sf::Font &font, const Cursors &cursors, const Colors &colors);
    void start(GameState &game_state);

    ~ChooseCharacterController() noexcept = default;
    ChooseCharacterController(ChooseCharacterController&&) noexcept = default;
    ChooseCharacterController& operator=(ChooseCharacterController&&) noexcept = delete;
    ChooseCharacterController(const ChooseCharacterController&) noexcept = delete;
    ChooseCharacterController& operator=(const ChooseCharacterController&) noexcept = delete;
};