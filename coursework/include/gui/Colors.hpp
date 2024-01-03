#pragma once
#include <SFML/Graphics/Color.hpp>

struct Colors final {
    sf::Color background_color;
    sf::Color text_color;
    Colors(const sf::Color background_color, const sf::Color text_color):
        background_color(background_color), text_color(text_color){}
};

struct ButtonColors final {
    sf::Color text_color;
    sf::Color active_color;
    ButtonColors(const sf::Color text_color, const sf::Color active_color):
        text_color(text_color), active_color(active_color){}
};

struct MenuColors final {
    Colors colors;
    ButtonColors button_colors;
    MenuColors(const Colors colors, const sf::Color active_color):
        colors(colors), button_colors(colors.text_color, active_color) {}
};