#pragma once
#include <string>
#include <vector>
#include <SFML/Graphics/Text.hpp>

#include "../../additionally/PixelConverter.hpp"

struct LoadingScreenInfo final {
    typedef std::vector<std::string> Strings;
    size_t pointer = 0;
    Strings strings;
    sf::Text text;
    LoadingScreenInfo(const sf::Font &font, Strings &&strings):
            strings(std::move(strings)), text(this->strings[pointer], font,
                PixelConverter::convertHeightToCurrentScreen(TEXT_SIZE)) { }
    LoadingScreenInfo(LoadingScreenInfo&& other) noexcept = default;
    ~LoadingScreenInfo() noexcept = default;
    LoadingScreenInfo& operator=(LoadingScreenInfo&&) noexcept = delete;
    LoadingScreenInfo(const LoadingScreenInfo&) noexcept = delete;
    LoadingScreenInfo& operator=(const LoadingScreenInfo&) noexcept = delete;
private:
    static constexpr unsigned TEXT_SIZE = 60;
};