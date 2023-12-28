#include "../../include/gui/Buttons.hpp"

Buttons::Buttons(const sf::Font &font): _font(&font) {}

void Buttons::setPos(const size_t i, const sf::Vector2f& p) {
    _buttons[i].setPos(p);
}

void Buttons::addButton(const std::string& label, std::function<void()> &&on_click_callback) {
    _buttons.emplace_back(label, *_font, std::move(on_click_callback));
}

void Buttons::handleClick(const sf::Vector2f& mouse) const {
    for (const auto& button : _buttons)
        button.handleClick(mouse);
}

MouseMovedRes Buttons::handleHoverTextColors(const sf::Vector2f& position) {
    MouseMovedRes result{0};
    for (auto& button : _buttons)
        result |= button.setHoverTextColor(position);
    return result;
}

void Buttons::draw(sf::RenderWindow& render_window) const {
    for (const auto& button : _buttons)
        button.draw(render_window);
}