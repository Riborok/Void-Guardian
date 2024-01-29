#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

#include "SettingsController.hpp"
#include "../Buttons.hpp"
#include "../Cursors.hpp"
#include "../../game/GameState.hpp"
#include "../../game/input/FullscreenToggler.hpp"

class PauseController final {
    static constexpr float BUTTON_SPACING = 98.0f;
    
    sf::RenderWindow *_window;
    FullscreenToggler *_fullscreen_toggler;
    Buttons _buttons;
    const Cursors *_cursors;
    sf::Color _background_color;
    GameState *_game_state = nullptr;

    void setButtonPos();
    void createMenu(const ButtonColors& button_colors, SettingsController &settings_controller);
    void drawPauseMenu() const;
    void handleKeyPressed(const sf::Keyboard::Key key);
    void handleEvents();
public:
    PauseController(GameContext &game_context, SettingsController &settings_controller, const sf::Font &font, const Cursors &cursors, const Colors &colors);
    void startPauseMenu(GameState &game_state);
    
    ~PauseController() noexcept = default;
    PauseController(PauseController&&) noexcept = default;
    PauseController& operator=(PauseController&&) noexcept = delete;
    PauseController(const PauseController&) noexcept = delete;
    PauseController& operator=(const PauseController&) noexcept = delete;
};
