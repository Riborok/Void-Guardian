#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

class FullscreenToggler final {
    sf::RenderWindow *_window;
    bool _is_fullscreen;
public:
    explicit FullscreenToggler(sf::RenderWindow& window, const bool set_fullscreen);

    void toggleFullscreen();

    ~FullscreenToggler() noexcept = default;
    FullscreenToggler(FullscreenToggler&&) noexcept = default;
    FullscreenToggler& operator=(FullscreenToggler&&) noexcept = default;
    
    FullscreenToggler(const FullscreenToggler&) noexcept = delete;
    FullscreenToggler& operator=(const FullscreenToggler&) noexcept = delete;
};
