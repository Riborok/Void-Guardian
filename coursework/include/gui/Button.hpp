// ReSharper disable CppClangTidyModernizeUseNodiscard
#pragma once
#include <functional>
#include <string>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include "Colors.hpp"
#include "MouseMovedRes.hpp"

class Button final {
public:
    typedef std::function<void()> Action;
private:
    static constexpr unsigned TEXT_SIZE = 30;
    sf::Text _text;
    ButtonColors _button_colors;
    Action _on_click_callback;
    bool contains(const sf::Vector2f &p) const;
public:
    Button(const std::string& label, const sf::Font &font, Action &&on_click_callback,
        const ButtonColors& button_colors);

    sf::Color getColor() const;
    void setStr(const std::string& str);
    void setOriginCenter();
    void setDefaultColor();
    void setColor(const sf::Color color);
    void draw(sf::RenderWindow &render_window) const;
    bool handleClick(const sf::Vector2f &mouse) const;
    MouseMovedRes setHoverTextColor(const sf::Vector2f &pos);
    void setPos(const sf::Vector2f &pos);

    ~Button() noexcept = default;
    Button(Button&&) noexcept = default;
    Button& operator=(Button&&) noexcept = default;
    Button(const Button&) noexcept = delete;
    Button& operator=(const Button&) noexcept = delete;
};