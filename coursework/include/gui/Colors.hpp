#pragma once
#include <SFML/Graphics/Color.hpp>

struct ButtonColors final {
    sf::Color text_color;
    sf::Color active_color;
    ButtonColors(const sf::Color text_color, const sf::Color active_color):
        text_color(text_color), active_color(active_color){}
};

struct Colors final {
    sf::Color background_color;
    ButtonColors button_colors;
    Colors(const sf::Color background_color, const sf::Color text_color, const sf::Color active_color):
        background_color(background_color), button_colors(text_color, active_color) {}
};

struct SettingColors final {
    Colors colors;
    sf::Color pressed_color;
    SettingColors(const Colors &menu_colors, const sf::Color pressed_color):
        colors(menu_colors), pressed_color(pressed_color){}
};