#include "../../include/gui/Buttons.hpp"

Buttons::Buttons(const sf::Font &font): _font(&font) {}

void Buttons::setPos(const size_t i, const sf::Vector2f& p) {
    _buttons[i].setPos(p);
}

void Buttons::addButton(const std::string& label, Button::Action &&on_click_callback, const ButtonColors& button_colors) {
    _buttons.emplace_back(label, *_font, std::move(on_click_callback), button_colors);
}

void Buttons::addButtonWidthOriginCenter(const std::string& label, Button::Action&& on_click_callback,
        const ButtonColors& button_colors) {
    _buttons.emplace_back(label, *_font, std::move(on_click_callback), button_colors).setOriginCenter();
}

bool Buttons::handleClick(const sf::Vector2f& mouse) const {
    bool result = false;
    for (const auto& button : _buttons)
        result |= button.handleClick(mouse);
    return result;
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

size_t Buttons::getCount() const { return _buttons.size(); }

sf::Color Buttons::getColor(const size_t index) const { return _buttons[index].getColor(); }

void Buttons::setColor(const size_t index, const sf::Color color) { _buttons[index].setColor(color); }

void Buttons::setDefaultColor() {
    for (auto& button : _buttons)
        button.setDefaultColor();
}

void Buttons::setStr(const size_t index, const std::string& str) {
    _buttons[index].setStr(str);
}