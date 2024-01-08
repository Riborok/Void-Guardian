#pragma once
#include <vector>
#include <SFML/Graphics/Text.hpp>

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
        return {
            {"Forward Move", font, TEXT_SIZE},
            {"Backward Move", font, TEXT_SIZE},
            {"Left Move", font, TEXT_SIZE},
            {"Right Move", font, TEXT_SIZE},
            {"Take", font, TEXT_SIZE},
            {"Fire", font, TEXT_SIZE}
        };
    }
};
