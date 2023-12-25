﻿#include "../../../include/game/input/FullscreenToggler.hpp"

FullscreenToggler::FullscreenToggler(sf::RenderWindow& window, WindowInfo &&window_info, const bool set_fullscreen):
            _window(&window), _window_info(std::move(window_info)),
            _is_fullscreen(set_fullscreen) { }

const std::string& FullscreenToggler::getTitle() const { return _window_info.title; }

void FullscreenToggler::toggleFullscreen() {
    _is_fullscreen = !_is_fullscreen;
    recreateWindow();
}

void FullscreenToggler::recreateWindow() const {
    _window->create(sf::VideoMode::getDesktopMode(), _window_info.title,
        _is_fullscreen ? sf::Style::Fullscreen : sf::Style::Default);

    if (sf::Image icon; icon.loadFromFile(_window_info.icon_src)) {
        _window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    }
}