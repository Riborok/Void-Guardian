﻿#pragma once
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

#include "toStr.hpp"

union KeyOrMouseButton final {
    sf::Keyboard::Key key;
    sf::Mouse::Button mouse_button;

    explicit KeyOrMouseButton(const sf::Keyboard::Key key) : key(key) {}
    explicit KeyOrMouseButton(const sf::Mouse::Button mb) : mouse_button(mb) {}
    KeyOrMouseButton() = default;
    
    bool operator==(const KeyOrMouseButton& other) const {
        return key == other.key && mouse_button == other.mouse_button;
    }
    bool operator!=(const KeyOrMouseButton& other) const {
        return !(*this == other);
    }
};

enum class InputType final {
    KEYBOARD,
    MOUSE_BUTTON
};

struct InputInfo final {
    InputType type;
    KeyOrMouseButton info;
    explicit InputInfo(const sf::Keyboard::Key key) : type(InputType::KEYBOARD), info(key) {}
    explicit InputInfo(const sf::Mouse::Button mb) : type(InputType::MOUSE_BUTTON), info(mb) {}
    InputInfo() = default;
    [[nodiscard]] std::string toString() const {
        switch (type) {
        case InputType::KEYBOARD:
            return sfKeyToStr(info.key);
        case InputType::MOUSE_BUTTON:
            return MBtoString(info.mouse_button);
        default:
            return "Unknown";    
        }
    }
    [[nodiscard]] bool idPressed() const {
        switch (type) {
        case InputType::KEYBOARD:
            return sf::Keyboard::isKeyPressed(info.key);
        case InputType::MOUSE_BUTTON:
            return sf::Mouse::isButtonPressed(info.mouse_button);
        default:
            return false;    
        }
    }
    bool operator==(const InputInfo& other) const {
        return type == other.type && info == other.info;
    }
    bool operator!=(const InputInfo& other) const {
        return !(*this == other);
    }
};