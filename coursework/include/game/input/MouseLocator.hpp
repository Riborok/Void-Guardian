#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Mouse.hpp>

class MouseLocator final {
    sf::RenderWindow *_window;
public:
    explicit MouseLocator(sf::RenderWindow &window): _window(&window) {}
    [[nodiscard]] sf::Vector2f getMousePos() const {
        return _window->mapPixelToCoords(sf::Mouse::getPosition(*_window));
    }
    
    ~MouseLocator() noexcept = default;
    MouseLocator(MouseLocator&&) noexcept = default;
    MouseLocator& operator=(MouseLocator&&) noexcept = delete;
    MouseLocator(const MouseLocator&) noexcept = delete;
    MouseLocator& operator=(const MouseLocator&) noexcept = delete;
};
