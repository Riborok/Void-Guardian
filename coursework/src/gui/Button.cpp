#include "../../include/gui/Button.hpp"

const unsigned Button::TEXT_SIZE = sf::VideoMode::getDesktopMode().height / 36;

bool Button::contains(const sf::Vector2f &p) const {
    return _text.getGlobalBounds().contains(p);
}

Button::Button(const std::string& label, const sf::Font &font, Action &&on_click_callback,
        const ButtonColors& button_colors): _text(label, font, TEXT_SIZE), _button_colors(button_colors),
        _on_click_callback(std::move(on_click_callback)) {
    _text.setFillColor(button_colors.text_color);
}

sf::Color Button::getColor() const { return _text.getFillColor(); }

void Button::setStr(const std::string& str) {
    _text.setString(str);
}

void Button::setOriginCenter() {
    const auto bounds = _text.getGlobalBounds();
    _text.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
}

void Button::setDefaultColor() { _text.setFillColor(_button_colors.text_color); }

void Button::setColor(const sf::Color color) { _text.setFillColor(color);  }

void Button::draw(sf::RenderWindow& render_window) const {
    render_window.draw(_text);
}

void Button::handleClick(const sf::Vector2f& mouse) const {
    if (contains(mouse))
        _on_click_callback();
}

MouseMovedRes Button::setHoverTextColor(const sf::Vector2f& pos) {
    const bool contains_pos = contains(pos);
    MouseMovedRes result         = contains_pos ? MouseMovedRes::SELECTION_CURSOR : MouseMovedRes::DEF_CURSOR;
    const sf::Color target_color = contains_pos ? _button_colors.active_color         : _button_colors.text_color;

    if (_text.getFillColor() != target_color) {
        result |= MouseMovedRes::REDRAW;
        _text.setFillColor(target_color);
    }
    
    return result;
}

void Button::setPos(const sf::Vector2f& pos) {
    _text.setPosition(pos);
}