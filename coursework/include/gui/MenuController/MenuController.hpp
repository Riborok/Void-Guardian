#pragma once
#include <SFML/Window/Keyboard.hpp>

#include "../Buttons.hpp"
#include "../Cursors.hpp"
#include "MenuControllerInfo.hpp"
#include "../../GameSetup.hpp"

class MenuController final {
    static float constexpr BUTTON_SPACING = 98.0f;
    bool _continue_menu = true;
    
    GameContext *_game_context;
    MenuControllerInfo _menu_controller_info;
    Buttons _buttons;
    const Cursors *_cursors;
    sf::Color _background_color;

    void setButtonPos();
    void createMenu(const ButtonColors& button_colors, SettingsController &settings_controller);
    void drawMenu() const;
    void handleKeyPressed(const sf::Keyboard::Key key) const;
    void handleEvents();
    void setDefaultTitle() const;
public:
    MenuController(GameSetup &game_setup, const sf::Font &font, const std::string &title, std::string &&about_url,
        const Cursors &cursors, const Colors &colors);
    
    void startMenu();
    
    ~MenuController() noexcept = default;
    MenuController(MenuController&&) noexcept = delete;
    MenuController& operator=(MenuController&&) noexcept = delete;
    MenuController(const MenuController&) noexcept = delete;
    MenuController& operator=(const MenuController&) noexcept = delete;
};
