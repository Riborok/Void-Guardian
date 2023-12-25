#pragma once
#include <array>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "Buttons.hpp"
#include "../files/PlayerProgress.hpp"
#include "../game/entity/player/Control.hpp"
#include "../game/input/FullscreenToggler.hpp"

// TODO: Make a normal MenuManager
class MenuManager final {
    typedef std::array<std::string, 4> AllButtonTypesStr;
    static constexpr size_t GAME_NAME_SIZE = 82;
    static constexpr float BUTTONS_SPACING = 50;

    bool _continue_menu = true;
    sf::RenderWindow *_window;
    FullscreenToggler *_fullscreen_toggler;
    sf::Font _font;
    Buttons _buttons;
    sf::Text _game_name;

    // TODO: Make settings
    PlayerProgress *_player_progress;
    Control *_control;

    void setButtonPos();
    void createMenu();
    void drawMenu() const;
    void processKeyPressed(const sf::Keyboard::Key &key) const;
    void processEvents();
public:
    MenuManager(sf::RenderWindow &window, FullscreenToggler &fullscreen_toggler,
        PlayerProgress &player_progress, Control &control,
        const std::string &font_src = "./AppData/font/BebasNeue Bold.ttf");
    
    void startMenu();
    
    ~MenuManager() noexcept = default;
    MenuManager(MenuManager&&) noexcept = default;
    MenuManager& operator=(MenuManager&&) noexcept = delete;
    MenuManager(const MenuManager&) noexcept = delete;
    MenuManager& operator=(const MenuManager&) noexcept = delete;
};
