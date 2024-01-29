#pragma once
#include "LoadingScreen.hpp"
#include "PauseController.hpp"
#include "SettingsController.hpp"

struct UIController final {
    const sf::Font *font;
    const Cursors *cursors;
    LoadingScreen loading_screen;
    SettingsController settings_controller;
    PauseController pause_controller;
    UIController(GameContext &game_context, const SettingColors &setting_colors,
            const sf::Font *font, const Cursors *cursors,
            LoadingScreenInfo::Strings &&loading_strings):
        font(font), cursors(cursors),
        loading_screen(game_context.window, game_context.fullscreen_toggler,
            {*font, std::move(loading_strings)}, cursors->normal_cursor, setting_colors.colors),
        settings_controller(game_context, *font, *cursors, setting_colors),
        pause_controller(game_context, settings_controller, *font, *cursors, setting_colors.colors){}
    ~UIController() { delete font; delete cursors; }
    UIController(UIController&& other) noexcept : font(other.font), cursors(other.cursors),
            loading_screen(std::move(other.loading_screen)), settings_controller(std::move(other.settings_controller)),
            pause_controller(std::move(other.pause_controller)){
        other.font = nullptr;
        other.cursors = nullptr;
    }
    UIController& operator=(UIController&&) noexcept = delete;
    UIController(const UIController&) noexcept = delete;
    UIController& operator=(const UIController&) noexcept = delete;
};