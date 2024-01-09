#pragma once
#include "CharacterVisualization.hpp"
#include "../GameState.hpp"
#include "../../GameContext.hpp"
#include "../../gui/Buttons.hpp"
#include "../../gui/Cursors.hpp"
#include "../processors/game loop/GameLoopState.hpp"

class ChooseCharacterManager final {
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
    void processKeyPressed(const sf::Keyboard::Key key);
    void processEvents();
public:
    ChooseCharacterManager(GameContext &game_context, AnimatedSprites &&sprites, CharacterInfos &character_infos,
        const sf::Font &font, const Cursors &cursors, const Colors &colors);
    void start(GameState &game_state);

    ~ChooseCharacterManager() noexcept = default;
    ChooseCharacterManager(ChooseCharacterManager&&) noexcept = default;
    ChooseCharacterManager& operator=(ChooseCharacterManager&&) noexcept = delete;
    ChooseCharacterManager(const ChooseCharacterManager&) noexcept = delete;
    ChooseCharacterManager& operator=(const ChooseCharacterManager&) noexcept = delete;
};