#pragma once
#include <string>
#include <SFML/Graphics/Text.hpp>

#include "../../additionally/PixelConverter.hpp"

struct MenuControllerInfo final {
    sf::Text game_name;
    std::string about_url;
    MenuControllerInfo(const sf::Font &font, const std::string &title, std::string &&about_url):
            game_name(title, font, PixelConverter::convertHeightToCurrentScreen(TEXT_SIZE)),
            about_url(std::move(about_url)) { }
    
    MenuControllerInfo(MenuControllerInfo&& other) noexcept = default;
    ~MenuControllerInfo() noexcept = default;
    MenuControllerInfo& operator=(MenuControllerInfo&&) noexcept = delete;
    MenuControllerInfo(const MenuControllerInfo&) noexcept = delete;
    MenuControllerInfo& operator=(const MenuControllerInfo&) noexcept = delete;
private:
    static constexpr unsigned TEXT_SIZE = 83;
};
