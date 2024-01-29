#pragma once
#include "SettingsButtons.hpp"
#include "../Buttons.hpp"
#include "../Cursors.hpp"
#include "SettingsControllerInfo.hpp"
#include "../../GameContext.hpp"

class SettingsController final {
    static float constexpr BUTTON_SPACING = 98.0f;
    static float constexpr INDENT = 64.0f;
    
    GameContext *_game_context;
    SettingsControllerInfo _settings_controller_info;
    SettingsButtons _settings_buttons;
    const Cursors *_cursors;
    sf::Color _background_color;
    bool _continue_settings = true;

    [[nodiscard]] float getMaxTextWidth() const;
    void handleKeyPressed(const sf::Keyboard::Key key);
    void setPositions();
    void createSettings(const ButtonColors& button_colors);
    void drawSettings();
    void handleEvents();
public:
    SettingsController(GameContext &game_context, const sf::Font &font, const Cursors &cursors,
        const SettingColors &setting_colors);

    void startSettings();
    
    ~SettingsController() noexcept = default;
    SettingsController(SettingsController&&) noexcept = default;
    SettingsController& operator=(SettingsController&&) noexcept = delete;
    SettingsController(const SettingsController&) noexcept = delete;
    SettingsController& operator=(const SettingsController&) noexcept = delete;
};