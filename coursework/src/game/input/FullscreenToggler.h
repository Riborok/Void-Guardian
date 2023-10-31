#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

#include "../../additionally/Constants.h"

class FullscreenToggler final {
    sf::RenderWindow *_window;
    bool _is_fullscreen;
public:
    explicit FullscreenToggler(sf::RenderWindow &window, const bool set_fullscreen): _window(&window), _is_fullscreen(set_fullscreen) { toggleFullscreen(); }
    void toggleFullscreen() {
        _window->create(sf::VideoMode::getDesktopMode(), Constants::TITLE, _is_fullscreen ? sf::Style::Fullscreen : sf::Style::Default);
        _is_fullscreen = !_is_fullscreen;
        
        sf::Image icon;
        if (icon.loadFromFile(Constants::ICON_SRC)) { _window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr()); }
    }

    ~FullscreenToggler() noexcept = default;
    FullscreenToggler(FullscreenToggler&&) noexcept = default;
    FullscreenToggler& operator=(FullscreenToggler&&) noexcept = default;
    
    FullscreenToggler(const FullscreenToggler&) noexcept = delete;
    FullscreenToggler& operator=(const FullscreenToggler&) noexcept = delete;
};
