#pragma once
#include <vector>

#include "Button.hpp"

// TODO: Make a normal Buttons
class Buttons final {
    std::vector<Button> _buttons;
    const sf::Font *_font;
public:
    explicit Buttons(const sf::Font &font);

    void setPos(const size_t i, const sf::Vector2f &p);
    void addButton(const std::string& label, std::function<void()> &&on_click_callback);
    void checkClick(const sf::Vector2f &mouse) const;
    void setColors(const sf::Vector2f &position);
    void draw(sf::RenderWindow &render_window) const;
    
    ~Buttons() noexcept = default;
    Buttons(Buttons&&) noexcept = default;
    Buttons& operator=(Buttons&&) noexcept = default;
    Buttons(const Buttons&) noexcept = delete;
    Buttons& operator=(const Buttons&) noexcept = delete;
};