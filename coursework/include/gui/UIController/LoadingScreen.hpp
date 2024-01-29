#pragma once

#include <SFML/System/Clock.hpp>
#include <SFML/Graphics.hpp>

#include "../Colors.hpp"
#include "LoadingScreenInfo.hpp"
#include "../../game/input/FullscreenToggler.hpp"

class LoadingScreen final {
    static constexpr int UPDATE_TIME = 742;
    
    sf::RenderWindow *_window;
    FullscreenToggler *_fullscreen_toggler;
    LoadingScreenInfo _loading_screen_info;
    const sf::Cursor *_default_cursor;
    sf::Color _background_color;
    sf::Clock _clock;
    volatile bool _continue_screen = true;

    void createText(const sf::Color color);
    void setTextBounds();
    void handleKeyPressed(const sf::Keyboard::Key key) const;
    void handleEvents() const;
    void redraw() const;
    void updateText();
    void setWindowParameters() const;
    void restoreSettings();
    void setTextStr();
public:
    LoadingScreen(sf::RenderWindow &window, FullscreenToggler &fullscreen_toggler, 
        LoadingScreenInfo &&loading_screen_info, const sf::Cursor &default_cursor, const Colors &colors);
    void start();
    void end();
    
    ~LoadingScreen() noexcept = default;
    LoadingScreen(LoadingScreen&&) noexcept = default;
    LoadingScreen& operator=(LoadingScreen&&) noexcept = delete;
    LoadingScreen(const LoadingScreen&) noexcept = delete;
    LoadingScreen& operator=(const LoadingScreen&) noexcept = delete;
};
