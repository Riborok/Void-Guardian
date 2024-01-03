#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "Buttons.hpp"
#include "MenuManagerInfo.hpp"
#include "../GameContext.hpp"

// TODO: Make a normal MenuManager
class MenuManager final {
    struct Cursors final {
        sf::Cursor normal_cursor;
        sf::Cursor selection_cursor;
        Cursors() {
            normal_cursor.loadFromSystem(sf::Cursor::Arrow);
            selection_cursor.loadFromSystem(sf::Cursor::Hand);
        }
    };
    
    Cursors _cursors;
    bool _continue_menu = true;

    // TODO: Make settings
    GameContext *_game_context;
    MenuManagerInfo _menu_manager_info;
    Buttons _buttons;
    sf::Color _background_color;

    void setButtonPos();
    void createMenu(const ButtonColors& button_colors);
    void drawMenu() const;
    void processKeyPressed(const sf::Keyboard::Key &key) const;
    void processEvents();
    void setDefaultTitle() const;
    void setDefaultView() const;
public:
    MenuManager(GameContext &game_context, MenuManagerInfo &&menu_manager_info, const MenuColors &menu_colors);
    
    void startMenu();
    
    ~MenuManager() noexcept = default;
    MenuManager(MenuManager&&) noexcept = delete;
    MenuManager& operator=(MenuManager&&) noexcept = delete;
    MenuManager(const MenuManager&) noexcept = delete;
    MenuManager& operator=(const MenuManager&) noexcept = delete;
};