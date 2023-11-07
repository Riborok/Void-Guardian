#pragma once
#include <unordered_set>
#include <SFML/Window/Keyboard.hpp>

class KeyHandler final {
    std::unordered_set<sf::Keyboard::Key> _keys;
public:
    void clearKeys();
    bool isKeyDown(const sf::Keyboard::Key key_code);
    void handleKeyDown(const sf::Keyboard::Key key_code);
    void handleKeyUp(const sf::Keyboard::Key key_code);

    KeyHandler() = default;
    ~KeyHandler() noexcept = default;
    
    KeyHandler(const KeyHandler&) noexcept = delete;
    KeyHandler& operator=(const KeyHandler&) noexcept = delete;
    KeyHandler(KeyHandler&&) noexcept = delete;
    KeyHandler& operator=(KeyHandler&&) noexcept = delete;
};
