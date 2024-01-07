#pragma once
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

#include "toStr.hpp"

union KeyOrMouseButton final {
    sf::Keyboard::Key key;
    sf::Mouse::Button mouse_button;

    explicit KeyOrMouseButton(const sf::Keyboard::Key key) : key(key) {}
    explicit KeyOrMouseButton(const sf::Mouse::Button mb) : mouse_button(mb) {}
    KeyOrMouseButton() = default;
};

enum class InputType final {
    KEYBOARD,
    MOUSE_BUTTON
};

struct InputData final {
    InputType type;
    KeyOrMouseButton data;
    explicit InputData(const sf::Keyboard::Key key) : type(InputType::KEYBOARD), data(key) {}
    explicit InputData(const sf::Mouse::Button mb) : type(InputType::MOUSE_BUTTON), data(mb) {}
    InputData() = default;
    [[nodiscard]] std::string toString() const {
        switch (type) {
        case InputType::KEYBOARD:
            return sfKeyToStr(data.key);
        case InputType::MOUSE_BUTTON:
            return MBtoString(data.mouse_button);
        default:
            return "Unknown";    
        }
    }
    [[nodiscard]] bool idPressed() const {
        switch (type) {
        case InputType::KEYBOARD:
            return sf::Keyboard::isKeyPressed(data.key);
        case InputType::MOUSE_BUTTON:
            return sf::Mouse::isButtonPressed(data.mouse_button);
        default:
            return false;    
        }
    }
};