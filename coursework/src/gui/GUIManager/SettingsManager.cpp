// ReSharper disable CppIncompleteSwitchStatement CppDefaultCaseNotHandledInSwitchStatement CppClangTidyClangDiagnosticSwitch CppClangTidyHicppMultiwayPathsCovered CppClangTidyClangDiagnosticSwitchEnum
#include <SFML/Window/Event.hpp>
#include "../../../include/gui/GUIManager/SettingsManager.hpp"
#include "../../../include/additionally/AdditionalFunc.hpp"

unsigned SettingsManager::getButtonSpacing() { return sf::VideoMode::getDesktopMode().height / 11; }

float SettingsManager::getIndent() { return static_cast<float>(sf::VideoMode::getDesktopMode().width) / 30.0f; }

std::vector<std::string> SettingsManager::getActionNames() const {
    const auto& control = _game_context->control;
    return {control.forward_move.toString(), control.backward_move.toString(),
        control.left_move.toString(), control.right_move.toString(), control.take_collectible.toString(),
        control.fire.toString()};
}

void SettingsManager::setActionNames() {
    const std::vector names(getActionNames());

    int i = 0;
    for (const auto& name : names) {
        _buttons.setStr(i, name);
        ++i;
    }
}

void SettingsManager::setInputData(const size_t index, const InputData &input_data) {
    _buttons.setStr(index, input_data.toString());
    
    auto& control = _game_context->control;
    switch (index) {
    case 0:
        control.forward_move = input_data;
        break;
    case 1:
        control.backward_move = input_data;
        break;
    case 2:
        control.left_move = input_data;
        break;
    case 3:
        control.right_move = input_data;
        break;
    case 4:
        control.take_collectible = input_data;
        break;
    case 5:
        control.fire = input_data;
        break;
    }

    _active_index = -1;
    drawSettings();
}


float SettingsManager::getMaxTextWidth() const {
    float result = 0;
    for (const auto& text : _settings_manager_info.texts)
        if (const float width(text.getGlobalBounds().width); result < width)
            result = width;
    return result;
}

void SettingsManager::setTextPos() {
    const auto window_size = _game_context->window.getSize();
    const float x_center = static_cast<float>(window_size.x) / 2.0f;
    const float y_start = static_cast<float>(window_size.y) / 7.0f;
    const float indent = getIndent();
    
    const float button_x = x_center + indent;
    const float text_x = x_center - getMaxTextWidth() - indent;
    const auto button_spacing = static_cast<float>(getButtonSpacing());
    float curr_y = y_start;
    const size_t count = _settings_manager_info.texts.size();
    for (size_t i = 0; i < count; ++i) {
        _buttons.setPos(i, {button_x, curr_y});
        _settings_manager_info.texts[i].setPosition({text_x, curr_y});
        curr_y += button_spacing;
    }
    _buttons.setPos(count, {x_center, curr_y});
}

void SettingsManager::processKeyPressed(const sf::Keyboard::Key& key) {
    switch (key) {
    case FullscreenToggler::DEFAULT_KEYBOARD_SWITCH:
        _game_context->fullscreen_toggler.toggleFullscreen();
        break;
    case sf::Keyboard::Escape:
        if (hasActiveButton()) {
            _active_index = -1;
            drawSettings();
        }
        else
            _continue_settings = false;
        break;
    default:
        if (hasActiveButton()) {
            setInputData(_active_index, InputData{key});
        }
        break;
    }
}

void SettingsManager::createSettings(const ButtonColors& button_colors) {
    const std::vector names(getActionNames());

    int i = 0;
    for (const auto& name : names) {
        _buttons.addButton(name, [this, i]{_active_index = i;}, button_colors);
        ++i;
    }
    _buttons.addButtonWidthOriginCenter("Return", [this]{_continue_settings = false;}, button_colors);
    
    for (auto& text : _settings_manager_info.texts)
        text.setFillColor(button_colors.text_color);
}

void SettingsManager::drawText() const {
    auto& window = _game_context->window;
    window.clear(_background_color);
    for (const auto& text : _settings_manager_info.texts)
        window.draw(text);
    _buttons.draw(window);
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
        case sf::Event::MouseButtonPressed:
            if (hasActiveButton())
                setInputData(_active_index, InputData{event.mouseButton.button});
            else if (event.mouseButton.button == sf::Mouse::Left)
                _buttons.handleClick(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
            break;
        case sf::Event::MouseMoved:
            const auto buttons_res(_buttons.handleHoverTextColors(window.mapPixelToCoords(sf::Mouse::getPosition(window))));

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

void SettingsManager::drawSettings() {
    if (hasActiveButton()) {
        const auto prev_color = _buttons.getColor(_active_index);
        _buttons.setColor(_active_index, _pressed_color);
        drawText();
        _buttons.setColor(_active_index, prev_color);
    }
    else
        drawText();
}

bool SettingsManager::hasActiveButton() const { return _active_index != -1; }

SettingsManager::SettingsManager(GameContext& game_context, SettingsManagerInfo&& settings_manager_info,
        const Cursors &cursors, const SettingColors &setting_colors): _game_context(&game_context),
        _settings_manager_info(std::move(settings_manager_info)), _buttons(*_settings_manager_info.texts[0].getFont()),
        _cursors(&cursors),
        _background_color(setting_colors.colors.background_color), _pressed_color(setting_colors.pressed_color) {
    createSettings(setting_colors.colors.button_colors);
    setTextPos();
}

void SettingsManager::startSettings() {
    AdditionalFunc::setDefaultView(_game_context->window);
    _buttons.setDefaultColor();
    setActionNames();
    drawSettings();

    _continue_settings = true;
    while (_continue_settings && _game_context->window.isOpen()) {
        processEvents();
    }
}