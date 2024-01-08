#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

#include "SettingsManager.hpp"
#include "../Buttons.hpp"
#include "../Cursors.hpp"
#include "../../game/GameState.hpp"
#include "../../game/input/FullscreenToggler.hpp"

class PauseManager final {
    static constexpr float BUTTON_SPACING = 98.0f;
    
    sf::RenderWindow *_window;
    FullscreenToggler *_fullscreen_toggler;
    Buttons _buttons;
    const Cursors *_cursors;
    sf::Color _background_color;
    GameState *_game_state = nullptr;

    void setButtonPos();
    void createMenu(const ButtonColors& button_colors, SettingsManager &settings_manager);
    void drawPauseMenu() const;
    void processKeyPressed(const sf::Keyboard::Key key);
    void processEvents();
public:
    PauseManager(GameContext &game_context, SettingsManager &settings_manager, const sf::Font &font, const Cursors &cursors, const Colors &colors);
    void startPauseMenu(GameState &game_state);
    
    ~PauseManager() noexcept = default;
    PauseManager(PauseManager&&) noexcept = default;
    PauseManager& operator=(PauseManager&&) noexcept = delete;
    PauseManager(const PauseManager&) noexcept = delete;
    PauseManager& operator=(const PauseManager&) noexcept = delete;
};
