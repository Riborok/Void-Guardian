#pragma once
#include <string>
#include <SFML/Graphics/Text.hpp>

struct MenuManagerInfo final {
    static constexpr size_t GAME_NAME_SIZE = 82;
    sf::Font font;
    sf::Text game_name;
    std::string about_url;
    MenuManagerInfo(const std::string &src, const std::string &title, std::string &&about_url):
            font(), game_name(title, font, GAME_NAME_SIZE), about_url(std::move(about_url)) {
        font.loadFromFile(src);
    }
    MenuManagerInfo(MenuManagerInfo&& other) noexcept:
            font(other.font), game_name(std::move(other.game_name)),
            about_url(std::move(other.about_url)) {
        game_name.setFont(font);
    }
    
    ~MenuManagerInfo() noexcept = default;
    MenuManagerInfo& operator=(MenuManagerInfo&&) noexcept = delete;
    MenuManagerInfo(const MenuManagerInfo&) noexcept = delete;
    MenuManagerInfo& operator=(const MenuManagerInfo&) noexcept = delete;
};