#include "../../include/game/WindowParam.hpp"

WindowParam::WindowParam(const sf::Vector2f &size) :
        _view(sf::FloatRect(0, 0, size.x, size.y)) {
    _window_half_size = size / 2.0f;
}
    
const sf::Vector2f& WindowParam::getWindowHalfSize() const { return _window_half_size; }
const sf::View& WindowParam::getView() const { return _view; }

void WindowParam::updateSize(const sf::Vector2f &size) {
    _window_half_size = size / 2.0f;
    _view.setSize(size);
}

void WindowParam::setFocus(const sf::Vector2f &focus) { _view.setCenter(focus); }
