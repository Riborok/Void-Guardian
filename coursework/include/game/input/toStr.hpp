// ReSharper disable CppClangTidyClangDiagnosticSwitchEnum
#pragma once
#include <string>
#include <SFML/Window/Keyboard.hpp>

inline std::string MBtoString(const sf::Mouse::Button button) {
    switch (button) {
    case sf::Mouse::Button::Left:
        return "Left Mouse Button";
    case sf::Mouse::Button::Right:
        return "Right Mouse Button";
    case sf::Mouse::Button::Middle:
        return "Middle Mouse Button";
    case sf::Mouse::Button::XButton1:
        return "X Button 1";
    case sf::Mouse::Button::XButton2:
        return "X Button 2";
    default:
        return "Unknown MouseButton";
    }
}

inline std::string sfKeyToStr(const sf::Keyboard::Key key) {
    if (key >= sf::Keyboard::A && key <= sf::Keyboard::Z)
        return {static_cast<char>('A' + (key - sf::Keyboard::A))};
    
    if (key >= sf::Keyboard::Num0 && key <= sf::Keyboard::Num9)
        return {static_cast<char>('0' + (key - sf::Keyboard::Num0))};

    if (key >= sf::Keyboard::Numpad0 && key <= sf::Keyboard::Numpad9)
        return "Numpad" + std::to_string(key - sf::Keyboard::Numpad0);

    if (key >= sf::Keyboard::F1 && key <= sf::Keyboard::F15)
        return "F" + std::to_string(key - sf::Keyboard::F1 + 1);
    
    switch (key) {
    case sf::Keyboard::Space: return "Space";
    case sf::Keyboard::Comma: return ",";
    case sf::Keyboard::Period: return ".";
    case sf::Keyboard::Hyphen: return "-";
    case sf::Keyboard::Quote: return "'";
    case sf::Keyboard::Slash: return "/";
    case sf::Keyboard::Backslash: return "\\";
    case sf::Keyboard::Semicolon: return ";";
    case sf::Keyboard::Equal: return "=";
    case sf::Keyboard::LBracket: return "[";
    case sf::Keyboard::RBracket: return "]";
    case sf::Keyboard::LShift: return "Left Shift";
    case sf::Keyboard::RShift: return "Right Shift";
    case sf::Keyboard::Unknown: return "Unknown Key";
    case sf::Keyboard::Escape: return "Escape";
    case sf::Keyboard::LControl: return "Left Control";
    case sf::Keyboard::LAlt: return "Left Alt";
    case sf::Keyboard::LSystem: return "Left System";
    case sf::Keyboard::RControl: return "Right Control";
    case sf::Keyboard::RAlt: return "Right Alt";
    case sf::Keyboard::RSystem: return "Right System";
    case sf::Keyboard::Menu: return "Menu";
    case sf::Keyboard::Tilde: return "Tilde";
    case sf::Keyboard::Enter: return "Enter";
    case sf::Keyboard::Backspace: return "Backspace";
    case sf::Keyboard::Tab: return "Tab";
    case sf::Keyboard::PageUp: return "Page Up";
    case sf::Keyboard::PageDown: return "Page Down";
    case sf::Keyboard::End: return "End";
    case sf::Keyboard::Home: return "Home";
    case sf::Keyboard::Insert: return "Insert";
    case sf::Keyboard::Delete: return "Delete";
    case sf::Keyboard::Add: return "Add";
    case sf::Keyboard::Subtract: return "Subtract";
    case sf::Keyboard::Multiply: return "Multiply";
    case sf::Keyboard::Divide: return "Divide";
    case sf::Keyboard::Left: return "Left";
    case sf::Keyboard::Right: return "Right";
    case sf::Keyboard::Up: return "Up";
    case sf::Keyboard::Down: return "Down";
    case sf::Keyboard::Pause: return "Pause";
    case sf::Keyboard::KeyCount: return "Key Count";
    default: return "Unknown Key";
    }
}