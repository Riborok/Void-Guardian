﻿#pragma once
#include "../Buttons.hpp"
#include "../Cursors.hpp"
#include "SettingsManagerInfo.hpp"
#include "../../GameContext.hpp"

class SettingsManager final {
    static unsigned getButtonSpacing();
    static float getIndent();
    [[nodiscard]] std::vector<std::string> getActionNames() const;
    void setActionNames();
    void setInputData(const size_t index, const InputData &input_data);
    
    GameContext *_game_context;
    SettingsManagerInfo _settings_manager_info;
    Buttons _buttons;
    const Cursors *_cursors;
    sf::Color _background_color;
    bool _continue_settings = true;
    
    int _active_index = -1;
    sf::Color _pressed_color;

    [[nodiscard]] float getMaxTextWidth() const;
    void processKeyPressed(const sf::Keyboard::Key& key);
    void setTextPos();
    void createSettings(const ButtonColors& button_colors);
    void drawText() const;
    void processEvents();
    void drawSettings();
    [[nodiscard]] bool hasActiveButton() const;
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
