﻿#include "../../include/gui/Buttons.hpp"

Buttons::Buttons(const sf::Font &font): _font(&font) {}

void Buttons::setPos(const size_t i, const sf::Vector2f& p) {
    _buttons[i].setPos(p);
}

void Buttons::addButton(const std::string& label, std::function<void()> &&on_click_callback) {
    _buttons.emplace_back(label, *_font, std::move(on_click_callback));
}

void Buttons::checkClick(const sf::Vector2f& mouse) const {
    for (const auto& button : _buttons)
        button.checkClick(mouse);
}

void Buttons::setColors(const sf::Vector2f& position) {
    for (auto& button : _buttons)
        button.setColor(position);
}

void Buttons::draw(sf::RenderWindow& render_window) const {
    for (const auto& button : _buttons)
        button.draw(render_window);
}