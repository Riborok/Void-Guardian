#include "../../../include/game/input/InputHandler.hpp"

void InputHandler::clear() {
    _mouse_buttons_mask = 0;
    _keys.clear();
}

bool InputHandler::isKeyDown(const sf::Keyboard::Key key_code) const {
    return _keys.find(key_code) != _keys.end();
}

void InputHandler::handleKeyDown(const sf::Keyboard::Key key_code) {
    _keys.insert(key_code);
}

void InputHandler::handleKeyUp(const sf::Keyboard::Key key_code) {
    _keys.erase(key_code);
}

void InputHandler::handleMouseDown(const sf::Mouse::Button button) {
    include(_mouse_buttons_mask, button);
}

void InputHandler::handleMouseUp(const sf::Mouse::Button button) {
    exclude(_mouse_buttons_mask, button);
}

bool InputHandler::isMouseDown(const MouseButton mouse_button) const {
    return has(_mouse_buttons_mask, mouse_button);
}

bool InputHandler::isDown(const InputData input_data) const {
    switch (input_data.type) {
    case InputType::KEYBOARD:
        return isKeyDown(input_data.data.key);
    case InputType::MOUSE_BUTTON:
        return isMouseDown(input_data.data.mouse_button);
    }
    return false;
}