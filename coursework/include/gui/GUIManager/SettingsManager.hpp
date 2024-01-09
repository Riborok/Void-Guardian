#pragma once
#include "SettingsButtons.hpp"
#include "../Buttons.hpp"
#include "../Cursors.hpp"
#include "SettingsManagerInfo.hpp"
#include "../../GameContext.hpp"

class SettingsManager final {
    static float constexpr BUTTON_SPACING = 98.0f;
    static float constexpr INDENT = 64.0f;
    
    GameContext *_game_context;
    SettingsManagerInfo _settings_manager_info;
    SettingsButtons _settings_buttons;
    const Cursors *_cursors;
    sf::Color _background_color;
    bool _continue_settings = true;

    [[nodiscard]] float getMaxTextWidth() const;
    void processKeyPressed(const sf::Keyboard::Key key);
    void setPositions();
    void createSettings(const ButtonColors& button_colors);
    void drawSettings();
    void processEvents();
public:
    SettingsManager(GameContext &game_context, SettingsManagerInfo &&settings_manager_info,
        const Cursors &cursors, const SettingColors &setting_colors);

    void startSettings();
    
    ~SettingsManager() noexcept = default;
    SettingsManager(SettingsManager&&) noexcept = default;
    SettingsManager& operator=(SettingsManager&&) noexcept = delete;
    SettingsManager(const SettingsManager&) noexcept = delete;
    SettingsManager& operator=(const SettingsManager&) noexcept = delete;
};