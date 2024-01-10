#pragma once
#include <SFML/Window/Keyboard.hpp>

#include "../Buttons.hpp"
#include "../Cursors.hpp"
#include "MenuManagerInfo.hpp"
#include "../../GameSetup.hpp"

class MenuManager final {
    static float constexpr BUTTON_SPACING = 98.0f;
    bool _continue_menu = true;
    
    GameContext *_game_context;
    MenuManagerInfo _menu_manager_info;
    Buttons _buttons;
    const Cursors *_cursors;
    sf::Color _background_color;

    void setButtonPos();
    void createMenu(const ButtonColors& button_colors, SettingsManager &settings_manager);
    void drawMenu() const;
    void processKeyPressed(const sf::Keyboard::Key key) const;
    void processEvents();
    void setDefaultTitle() const;
public:
    MenuManager(GameSetup &game_setup, const sf::Font &font, const std::string &title, std::string &&about_url,
        const Cursors &cursors, const Colors &colors);
    
    void startMenu();
    
    ~MenuManager() noexcept = default;
    MenuManager(MenuManager&&) noexcept = delete;
    MenuManager& operator=(MenuManager&&) noexcept = delete;
    MenuManager(const MenuManager&) noexcept = delete;
    MenuManager& operator=(const MenuManager&) noexcept = delete;
};
