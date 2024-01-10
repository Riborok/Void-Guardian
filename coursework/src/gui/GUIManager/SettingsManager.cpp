// ReSharper disable CppIncompleteSwitchStatement CppDefaultCaseNotHandledInSwitchStatement CppClangTidyClangDiagnosticSwitch CppClangTidyHicppMultiwayPathsCovered CppClangTidyClangDiagnosticSwitchEnum
#include <SFML/Window/Event.hpp>
#include "../../../include/gui/GUIManager/SettingsManager.hpp"
#include "../../../include/additionally/AdditionalFunc.hpp"
#include "../../../include/additionally/PixelConverter.hpp"
#include "../../../include/gui/ReservedKeys.hpp"

float SettingsManager::getMaxTextWidth() const {
    float result = 0;
    for (const auto& text : _settings_manager_info.texts)
        if (const float width(text.getGlobalBounds().width); result < width)
            result = width;
    return result;
}

void SettingsManager::setPositions() {
    const auto window_size = _game_context->window.getSize();
    const float x_center = static_cast<float>(window_size.x) / 2.0f;
    const float y_start = static_cast<float>(window_size.y) / 7.0f;
    const float button_spacing(PixelConverter::convertHeightToCurrentScreen(BUTTON_SPACING));
    const float indent(PixelConverter::convertWidthToCurrentScreen(INDENT));
    
    const float button_x = x_center + indent;
    const float text_x = x_center - getMaxTextWidth() - indent;
    float curr_y = y_start;
    const size_t count = _settings_manager_info.texts.size();
    for (size_t i = 0; i < count; ++i) {
        _settings_buttons.setPos(i, {button_x, curr_y});
        _settings_manager_info.texts[i].setPosition({text_x, curr_y});
        curr_y += button_spacing;
    }
    _settings_buttons.setPos(count, {x_center, curr_y});
}

void SettingsManager::processKeyPressed(const sf::Keyboard::Key key) {
    switch (key) {
    case ReservedKeys::FULL_SCREEN_TOGGLE:
        _game_context->fullscreen_toggler.toggleFullscreen(_cursors->normal_cursor);
        drawSettings();
        break;
    case ReservedKeys::BACK:
        if (_settings_buttons.hasActiveButton()) {
            _settings_buttons.resetActiveIndex();
            drawSettings();
        }
        else
            _continue_settings = false;
        break;
    default:
        if (_settings_buttons.hasActiveButton()) {
            _settings_buttons.setInputData(InputData{key});
            drawSettings();
        }
        break;
    }
}

void SettingsManager::createSettings(const ButtonColors& button_colors) {
    _settings_buttons.createButtons(_continue_settings, button_colors);
    
    for (auto& text : _settings_manager_info.texts)
        text.setFillColor(button_colors.text_color);
}

void SettingsManager::drawSettings() {
    auto& window = _game_context->window;
    window.clear(_background_color);
    for (const auto& text : _settings_manager_info.texts)
        window.draw(text);
    _settings_buttons.draw(window);
    window.display();
}

void SettingsManager::processEvents() {
    auto& window = _game_context->window;
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::KeyPressed:
            processKeyPressed(event.key.code);
            break;
        case sf::Event::MouseButtonReleased:
            if (_settings_buttons.hasActiveButton()) {
                _settings_buttons.setInputData(InputData{event.mouseButton.button});
                drawSettings();
            }
            else if (event.mouseButton.button == sf::Mouse::Left &&
                    _settings_buttons.handleClick(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                drawSettings();
            break;
        case sf::Event::MouseMoved:
            const auto buttons_res(_settings_buttons.handleHoverTextColors(window.mapPixelToCoords(sf::Mouse::getPosition(window))));

            if (has(buttons_res, MouseMovedRes::REDRAW))
                drawSettings();

            if (has(buttons_res, MouseMovedRes::SELECTION_CURSOR))
                window.setMouseCursor(_cursors->selection_cursor);
            else
                window.setMouseCursor(_cursors->normal_cursor);
            break;
        }
    }
}

SettingsManager::SettingsManager(GameContext& game_context, const sf::Font &font, const Cursors &cursors,
    const SettingColors &setting_colors): _game_context(&game_context),
        _settings_manager_info(font),
        _settings_buttons(game_context.control, font, setting_colors.pressed_color),
        _cursors(&cursors), _background_color(setting_colors.colors.background_color) {
    createSettings(setting_colors.colors.button_colors);
    setPositions();
}

void SettingsManager::startSettings() {
    AdditionalFunc::setDefaultView(_game_context->window);
    _settings_buttons.setDefaultColor();
    _settings_buttons.setActionNames();
    drawSettings();

    _continue_settings = true;
    while (_continue_settings && _game_context->window.isOpen()) {
        processEvents();
    }
}