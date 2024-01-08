#pragma once
#include <vector>

#include "Button.hpp"

class Buttons final {
    typedef std::vector<Button> ButtonVector;
    ButtonVector _buttons;
    const sf::Font *_font;
public:
    explicit Buttons(const sf::Font &font);

    void setPos(const size_t i, const sf::Vector2f &p);
    void addButton(const std::string& label, Button::Action &&on_click_callback, const ButtonColors& button_colors);
    void addButtonWidthOriginCenter(const std::string& label, Button::Action &&on_click_callback, const ButtonColors& button_colors);
    void handleClick(const sf::Vector2f &mouse) const;
    MouseMovedRes handleHoverTextColors(const sf::Vector2f &position);
    void draw(sf::RenderWindow &render_window) const;
    [[nodiscard]] size_t getCount() const;
    [[nodiscard]] sf::Color getColor(const size_t index) const;
    void setColor(const size_t index, const sf::Color color);
    void setDefaultColor();
    void setStr(const size_t index, const std::string& str);
    
    ~Buttons() noexcept = default;
    Buttons(Buttons&&) noexcept = default;
    Buttons& operator=(Buttons&&) noexcept = default;
    Buttons(const Buttons&) noexcept = delete;
    Buttons& operator=(const Buttons&) noexcept = delete;
};