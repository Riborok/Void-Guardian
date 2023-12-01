#pragma once
#include <SFML/Window/Keyboard.hpp>

#include "MouseButton.hpp"

union KeyOrMouseButton final {
    sf::Keyboard::Key key;
    MouseButton mouse_button;

    explicit KeyOrMouseButton(const sf::Keyboard::Key key) : key(key) {}
    explicit KeyOrMouseButton(const MouseButton mb) : mouse_button(mb) {}
};

enum class InputType final {
    KEYBOARD,
    MOUSE_BUTTON
};

struct InputData final {
    InputType type;
    KeyOrMouseButton data;
    explicit InputData(const sf::Keyboard::Key key) : type(InputType::KEYBOARD), data(key) {}
    explicit InputData(const MouseButton mb) : type(InputType::MOUSE_BUTTON), data(mb) {}
};