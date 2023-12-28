#pragma once
#include <functional>
#include <string>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include "MouseMovedRes.hpp"

struct ButtonColors final {
    sf::Color text_color;
    sf::Color active_color;
    explicit ButtonColors(const sf::Color text_color, const sf::Color active_color):
        text_color(text_color), active_color(active_color){}
};

// TODO: Make a normal Button
class Button final {
    static constexpr int TEXT_SIZE = 30;
    sf::Text _text;
    ButtonColors _button_colors;
    std::function<void()> _on_click_callback;
    bool contains(const sf::Vector2f &p) const;
public:
    Button(const std::string& label, const sf::Font &font, std::function<void()> &&on_click_callback,
        const ButtonColors& button_colors = ButtonColors{sf::Color::White, sf::Color::Yellow});
    
    void draw(sf::RenderWindow &render_window) const;
    void handleClick(const sf::Vector2f &mouse) const;
    MouseMovedRes setHoverTextColor(const sf::Vector2f &pos);
    void setPos(const sf::Vector2f &pos);

    ~Button() noexcept = default;
    Button(Button&&) noexcept = default;
    Button& operator=(Button&&) noexcept = default;
    Button(const Button&) noexcept = delete;
    Button& operator=(const Button&) noexcept = delete;
};