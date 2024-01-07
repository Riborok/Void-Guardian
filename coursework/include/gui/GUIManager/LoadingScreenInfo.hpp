#pragma once
#include <string>
#include <vector>
#include <SFML/Graphics/Text.hpp>

struct LoadingScreenInfo final {
    size_t pointer = 0;
    std::vector<std::string> strings;
    sf::Text text;
    LoadingScreenInfo(const sf::Font &font, std::vector<std::string> &&strings):
            strings(std::move(strings)), text(this->strings[pointer], font, getTextSize()) { }
    LoadingScreenInfo(LoadingScreenInfo&& other) noexcept = default;
    ~LoadingScreenInfo() noexcept = default;
    LoadingScreenInfo& operator=(LoadingScreenInfo&&) noexcept = delete;
    LoadingScreenInfo(const LoadingScreenInfo&) noexcept = delete;
    LoadingScreenInfo& operator=(const LoadingScreenInfo&) noexcept = delete;
private:
    static unsigned getTextSize() { return sf::VideoMode::getDesktopMode().height / 18; }
};