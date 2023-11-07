#include "../../../include/game/input/FullscreenToggler.hpp"

#include "../../../include/additionally/Constants.hpp"

FullscreenToggler::FullscreenToggler(sf::RenderWindow& window, const bool set_fullscreen)
    : _window(&window), _is_fullscreen(set_fullscreen) {
    toggleFullscreen();
}

void FullscreenToggler::toggleFullscreen() {
    _window->create(sf::VideoMode::getDesktopMode(), Constants::TITLE,
        _is_fullscreen ? sf::Style::Fullscreen : sf::Style::Default);
    _is_fullscreen = !_is_fullscreen;

    if (sf::Image icon; icon.loadFromFile(Constants::ICON_SRC)) {
        _window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    }
}