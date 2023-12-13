#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

class FullscreenToggler final {
    sf::RenderWindow *_window;
    std::string _title;
    std::string _icon_src;
    bool _is_fullscreen;
public:
    FullscreenToggler(sf::RenderWindow& window, std::string title,
                      std::string icon_src, const bool set_fullscreen);

    void toggleFullscreen();

    ~FullscreenToggler() noexcept = default;
    FullscreenToggler(FullscreenToggler&&) noexcept = default;
    FullscreenToggler& operator=(FullscreenToggler&&) noexcept = delete;
    
    FullscreenToggler(const FullscreenToggler&) noexcept = delete;
    FullscreenToggler& operator=(const FullscreenToggler&) noexcept = delete;
};
