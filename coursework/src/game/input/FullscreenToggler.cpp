#include "../../../include/game/input/FullscreenToggler.hpp"

FullscreenToggler::FullscreenToggler(sf::RenderWindow& window, std::string title,
                                     std::string icon_src, const bool set_fullscreen):
            _window(&window), _title(std::move(title)), _icon_src(std::move(icon_src)),
            _is_fullscreen(set_fullscreen) {
    toggleFullscreen();
}

void FullscreenToggler::toggleFullscreen() {
    _window->create(sf::VideoMode::getDesktopMode(), _title,
        _is_fullscreen ? sf::Style::Fullscreen : sf::Style::Default);
    _is_fullscreen = !_is_fullscreen;

    if (sf::Image icon; icon.loadFromFile(_icon_src)) {
        _window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    }
}