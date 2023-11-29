#include "../../../include/game/input/KeyHandler.hpp"

void KeyHandler::clearKeys() {
    _keys.clear();
}

bool KeyHandler::isKeyDown(const sf::Keyboard::Key key_code) const {
    return _keys.find(key_code) != _keys.end();
}

void KeyHandler::handleKeyDown(const sf::Keyboard::Key key_code) {
    _keys.insert(key_code);
}

void KeyHandler::handleKeyUp(const sf::Keyboard::Key key_code) {
    _keys.erase(key_code);
}