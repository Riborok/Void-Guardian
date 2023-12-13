#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include "WindowInfo.hpp"

class FullscreenToggler final {
    sf::RenderWindow *_window;
    WindowInfo _window_info;
    bool _is_fullscreen;
public:
    FullscreenToggler(sf::RenderWindow& window, WindowInfo window_info, const bool set_fullscreen);

    void toggleFullscreen();

    ~FullscreenToggler() noexcept = default;
    FullscreenToggler(FullscreenToggler&&) noexcept = default;
    FullscreenToggler& operator=(FullscreenToggler&&) noexcept = delete;
    
    FullscreenToggler(const FullscreenToggler&) noexcept = delete;
    FullscreenToggler& operator=(const FullscreenToggler&) noexcept = delete;
};
