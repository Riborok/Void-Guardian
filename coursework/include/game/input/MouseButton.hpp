// ReSharper disable CppDefaultCaseNotHandledInSwitchStatement CppIncompleteSwitchStatement CppClangTidyClangDiagnosticSwitch CppClangTidyBugproneBranchClone
#pragma once
#include <SFML/Window/Mouse.hpp>

typedef size_t MouseButtonsMask;
enum class MouseButton final : MouseButtonsMask {
    LEFT        = 1 << 0,    
    RIGHT       = 1 << 1,  
    MIDDLE      = 1 << 2,   
    X_BUTTON1   = 1 << 3,  
    X_BUTTON2   = 1 << 4, 
};

constexpr bool has(const MouseButtonsMask mask, const MouseButton mouse_buttons) {
    return mask & static_cast<MouseButtonsMask>(mouse_buttons);
}

constexpr void include(MouseButtonsMask &mask, const sf::Mouse::Button button) {
    switch (button) {
    case sf::Mouse::Left:
        mask |= static_cast<MouseButtonsMask>(MouseButton::LEFT);
        break;
    case sf::Mouse::Right:
        mask |= static_cast<MouseButtonsMask>(MouseButton::RIGHT);
        break;
    case sf::Mouse::Middle:
        mask |= static_cast<MouseButtonsMask>(MouseButton::MIDDLE);
        break;
    case sf::Mouse::XButton1:
        mask |= static_cast<MouseButtonsMask>(MouseButton::X_BUTTON1);
        break;
    case sf::Mouse::XButton2:
        mask |= static_cast<MouseButtonsMask>(MouseButton::X_BUTTON2);
        break;
    }
}

constexpr void exclude(MouseButtonsMask &mask, const sf::Mouse::Button button) {
    switch (button) {
    case sf::Mouse::Left:
        mask &= ~static_cast<MouseButtonsMask>(MouseButton::LEFT);
        break;
    case sf::Mouse::Right:
        mask &= ~static_cast<MouseButtonsMask>(MouseButton::RIGHT);
        break;
    case sf::Mouse::Middle:
        mask &= ~static_cast<MouseButtonsMask>(MouseButton::MIDDLE);
        break;
    case sf::Mouse::XButton1:
        mask &= ~static_cast<MouseButtonsMask>(MouseButton::X_BUTTON1);
        break;
    case sf::Mouse::XButton2:
        mask &= ~static_cast<MouseButtonsMask>(MouseButton::X_BUTTON2);
        break;
    }
}