#include "../../include/gui/Button.hpp"

bool Button::contains(const sf::Vector2f &p) const {
    return _text.getGlobalBounds().contains(p);
}

Button::Button(const std::string& label, const sf::Font &font, std::function<void()> &&on_click_callback,
        const ButtonColors& button_colors): _text(label, font, TEXT_SIZE), _button_colors(button_colors),
        _on_click_callback(std::move(on_click_callback)) {
    _text.setFillColor(button_colors.text_color);
    _text.setOrigin(_text.getGlobalBounds().width / 2.0f, _text.getGlobalBounds().height / 2.0f);
}

void Button::draw(sf::RenderWindow& render_window) const {
    render_window.draw(_text);
}

void Button::checkClick(const sf::Vector2f& mouse) const {
    if (contains(mouse))
        _on_click_callback();
}

void Button::setColor(const sf::Vector2f& position) {
    if (contains(position)) { _text.setFillColor(_button_colors.active_color); }
    else                    { _text.setFillColor(_button_colors.text_color); }
}

void Button::setPos(const sf::Vector2f& p) {
    _text.setPosition(p);
}