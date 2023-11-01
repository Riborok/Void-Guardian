#pragma once
#include <unordered_set>
#include <SFML/Window/Keyboard.hpp>

class KeyHandler final {
    std::unordered_set<sf::Keyboard::Key> _keys;
public:
    void clearKeys() {
        _keys.clear();
    }
    bool isKeyDown(const sf::Keyboard::Key key_code) {
        return _keys.find(key_code) != _keys.end();
    }
    void handleKeyDown(const sf::Keyboard::Key key_code) {
        _keys.insert(key_code);
    }
    void handleKeyUp(const sf::Keyboard::Key key_code) {
        _keys.erase(key_code);
    }

    KeyHandler() = default;
    ~KeyHandler() noexcept = default;
    
    KeyHandler(const KeyHandler&) noexcept = delete;
    KeyHandler& operator=(const KeyHandler&) noexcept = delete;
    KeyHandler(KeyHandler&&) noexcept = delete;
    KeyHandler& operator=(KeyHandler&&) noexcept = delete;
};
