#pragma once
#include <vector>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/VideoMode.hpp>

struct SettingsManagerInfo final {
    std::vector<sf::Text> texts;
    explicit SettingsManagerInfo(const sf::Font &font):texts(getTexts(font)) {}
    
    SettingsManagerInfo(SettingsManagerInfo&& other) noexcept = default;
    ~SettingsManagerInfo() noexcept = default;
    SettingsManagerInfo& operator=(SettingsManagerInfo&&) noexcept = delete;
    SettingsManagerInfo(const SettingsManagerInfo&) noexcept = delete;
    SettingsManagerInfo& operator=(const SettingsManagerInfo&) noexcept = delete;
private:
    static unsigned getTextSize() { return sf::VideoMode::getDesktopMode().height / 36; }
    static std::vector<sf::Text> getTexts(const sf::Font &font) {
        const auto size(getTextSize());
        return {
            {"Forward Move", font, size},
            {"Backward Move", font, size},
            {"Left Move", font, size},
            {"Right Move", font, size},
            {"Take", font, size},
            {"Fire", font, size}
        };
    }
};
