#pragma once
#include <vector>
#include <SFML/Graphics/Text.hpp>

#include "../../additionally/PixelConverter.hpp"

struct SettingsControllerInfo final {
    typedef std::vector<sf::Text> Texts;
    Texts texts;
    explicit SettingsControllerInfo(const sf::Font &font):texts(getTexts(font)) {}
    
    SettingsControllerInfo(SettingsControllerInfo&& other) noexcept = default;
    ~SettingsControllerInfo() noexcept = default;
    SettingsControllerInfo& operator=(SettingsControllerInfo&&) noexcept = delete;
    SettingsControllerInfo(const SettingsControllerInfo&) noexcept = delete;
    SettingsControllerInfo& operator=(const SettingsControllerInfo&) noexcept = delete;
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
