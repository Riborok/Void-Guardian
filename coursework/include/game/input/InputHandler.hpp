#pragma once
#include <unordered_set>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

#include "InputData.hpp"
#include "MouseButton.hpp"

class InputHandler final {
    typedef std::unordered_set<sf::Keyboard::Key> Keys;
    
    Keys _keys;
    MouseButtonsMask _mouse_buttons_mask = 0; 
public:
    void clear();
    
    [[nodiscard]] bool isKeyDown(const sf::Keyboard::Key key_code) const;
    void handleKeyDown(const sf::Keyboard::Key key_code);
    void handleKeyUp(const sf::Keyboard::Key key_code);

    void handleMouseDown(const sf::Mouse::Button button);
    void handleMouseUp(const sf::Mouse::Button button);
    [[nodiscard]] bool isMouseDown(const MouseButton mouse_button) const;

    [[nodiscard]] bool isDown(const InputData input_data) const;

    InputHandler() noexcept = default;
    ~InputHandler() noexcept = default;
    
    InputHandler(const InputHandler&) noexcept = delete;
    InputHandler& operator=(const InputHandler&) noexcept = delete;
    InputHandler(InputHandler&&) noexcept = delete;
    InputHandler& operator=(InputHandler&&) noexcept = delete;
};
