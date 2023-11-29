#pragma once
#include <unordered_set>
#include <SFML/Window/Keyboard.hpp>

class KeyHandler final {
    typedef std::unordered_set<sf::Keyboard::Key> Keys;
    
    Keys _keys;
public:
    void clearKeys();
    [[nodiscard]] bool isKeyDown(const sf::Keyboard::Key key_code) const;
    void handleKeyDown(const sf::Keyboard::Key key_code);
    void handleKeyUp(const sf::Keyboard::Key key_code);

    KeyHandler() noexcept = default;
    ~KeyHandler() noexcept = default;
    
    KeyHandler(const KeyHandler&) noexcept = delete;
    KeyHandler& operator=(const KeyHandler&) noexcept = delete;
    KeyHandler(KeyHandler&&) noexcept = delete;
    KeyHandler& operator=(KeyHandler&&) noexcept = delete;
};
