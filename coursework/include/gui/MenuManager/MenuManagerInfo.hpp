#pragma once
#include <string>
#include <SFML/Graphics/Text.hpp>

struct MenuManagerInfo final {
    sf::Text game_name;
    std::string about_url;
    MenuManagerInfo(const sf::Font &font, const std::string &title, std::string &&about_url):
            game_name(title, font, getTextSize()), about_url(std::move(about_url)) { }
    
    MenuManagerInfo(MenuManagerInfo&& other) noexcept = default;
    ~MenuManagerInfo() noexcept = default;
    MenuManagerInfo& operator=(MenuManagerInfo&&) noexcept = delete;
    MenuManagerInfo(const MenuManagerInfo&) noexcept = delete;
    MenuManagerInfo& operator=(const MenuManagerInfo&) noexcept = delete;
private:
    static unsigned getTextSize() { return sf::VideoMode::getDesktopMode().height / 13; }
};