#pragma once
#include <string>
#include <vector>
#include <SFML/Graphics/Text.hpp>

struct LoadingScreenInfo final {
    sf::Font font;
    size_t pointer = 0;
    std::vector<std::string> strings;
    sf::Text text;
    LoadingScreenInfo(const std::string &src, std::vector<std::string> &&strings):
            strings(std::move(strings)), text(this->strings[pointer], font, getTextSize()) {
        font.loadFromFile(src);
    }
    LoadingScreenInfo(LoadingScreenInfo&& other) noexcept:
            font(other.font), pointer(other.pointer),
            strings(std::move(other.strings)), text(std::move(other.text)) {
        text.setFont(font);
    }
    ~LoadingScreenInfo() noexcept = default;
    LoadingScreenInfo& operator=(LoadingScreenInfo&&) noexcept = delete;
    LoadingScreenInfo(const LoadingScreenInfo&) noexcept = delete;
    LoadingScreenInfo& operator=(const LoadingScreenInfo&) noexcept = delete;
private:
    static unsigned getTextSize() { return sf::VideoMode::getDesktopMode().height / 18; }
};