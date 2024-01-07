#pragma once
#include <vector>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/VideoMode.hpp>

struct SettingsManagerInfo final {
    sf::Font font;
    std::vector<sf::Text> texts;

    explicit SettingsManagerInfo(const std::string &src):
            font(), texts(getTexts()){
        font.loadFromFile(src);
    }
    
    SettingsManagerInfo(SettingsManagerInfo&& other) noexcept:
        font(other.font), texts(std::move(other.texts)) {
        for (auto& text : texts)
            text.setFont(font);
    }
    
    ~SettingsManagerInfo() noexcept = default;
    SettingsManagerInfo& operator=(SettingsManagerInfo&&) noexcept = delete;
    SettingsManagerInfo(const SettingsManagerInfo&) noexcept = delete;
    SettingsManagerInfo& operator=(const SettingsManagerInfo&) noexcept = delete;
private:
    static unsigned getTextSize() { return sf::VideoMode::getDesktopMode().height / 36; }
    std::vector<sf::Text> getTexts() {
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
