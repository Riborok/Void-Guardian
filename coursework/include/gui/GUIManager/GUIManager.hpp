﻿#pragma once
#include "LoadingScreen.hpp"
#include "PauseManager.hpp"
#include "SettingsManager.hpp"

struct GUIManager final {
    const sf::Font *font;
    const Cursors *cursors;
    LoadingScreen loading_screen;
    SettingsManager settings_manager;
    PauseManager pause_manager;
    GUIManager(GameContext &game_context, const SettingColors &setting_colors,
            const sf::Font *font, const Cursors *cursors,
            LoadingScreenInfo::Strings &&loading_strings):
        font(font), cursors(cursors),
        loading_screen(game_context.window, game_context.fullscreen_toggler,
            {*font, std::move(loading_strings)}, cursors->normal_cursor, setting_colors.colors),
        settings_manager(game_context, *font, *cursors, setting_colors),
        pause_manager(game_context, settings_manager, *font, *cursors, setting_colors.colors){}
    ~GUIManager() { delete font; delete cursors; }
    GUIManager(GUIManager&& other) noexcept : font(other.font), cursors(other.cursors),
            loading_screen(std::move(other.loading_screen)), settings_manager(std::move(other.settings_manager)),
            pause_manager(std::move(other.pause_manager)){
        other.font = nullptr;
        other.cursors = nullptr;
    }
    GUIManager& operator=(GUIManager&&) noexcept = delete;
    GUIManager(const GUIManager&) noexcept = delete;
    GUIManager& operator=(const GUIManager&) noexcept = delete;
};