#pragma once
#include <SFML/Window/Keyboard.hpp>

#include "Buttons.hpp"
#include "Cursors.hpp"
#include "MenuManagerInfo.hpp"
#include "../GameSetup.hpp"

class MenuManager final {
    static unsigned getButtonSpacing();
    
    Cursors _cursors;
    bool _continue_menu = true;

    // TODO: Make settings
    GameSetup *_game_setup;
    MenuManagerInfo _menu_manager_info;
    Buttons _buttons;
    sf::Color _background_color;

    void setButtonPos();
    void createMenu(const ButtonColors& button_colors);
    void drawMenu() const;
    void processKeyPressed(const sf::Keyboard::Key &key) const;
    void processEvents();
    void setDefaultTitle() const;
public:
    MenuManager(GameSetup &game_setup, MenuManagerInfo &&menu_manager_info, const MenuColors &menu_colors);
    
    void startMenu();
    
    ~MenuManager() noexcept = default;
    MenuManager(MenuManager&&) noexcept = delete;
    MenuManager& operator=(MenuManager&&) noexcept = delete;
    MenuManager(const MenuManager&) noexcept = delete;
    MenuManager& operator=(const MenuManager&) noexcept = delete;
};
