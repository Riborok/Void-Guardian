#pragma once
#include <vector>
#include <SFML/Graphics/Text.hpp>

#include "../../additionally/PixelConverter.hpp"

struct SettingsManagerInfo final {
    typedef std::vector<sf::Text> Texts;
    Texts texts;
    explicit SettingsManagerInfo(const sf::Font &font):texts(getTexts(font)) {}
    
    SettingsManagerInfo(SettingsManagerInfo&& other) noexcept = default;
    ~SettingsManagerInfo() noexcept = default;
    SettingsManagerInfo& operator=(SettingsManagerInfo&&) noexcept = delete;
    SettingsManagerInfo(const SettingsManagerInfo&) noexcept = delete;
    SettingsManagerInfo& operator=(const SettingsManagerInfo&) noexcept = delete;
private:
    static constexpr unsigned TEXT_SIZE = 30;
    static Texts getTexts(const sf::Font &font) {
        const unsigned text_size(PixelConverter::convertHeightToCurrentScreen(TEXT_SIZE));
        return {
            {"Forward Move", font, text_size},
            {"Backward Move", font, text_size},
            {"Left Move", font, text_size},
            {"Right Move", font, text_size},
            {"Take", font, text_size},
            {"Fire", font, text_size}
        };
    }
};
