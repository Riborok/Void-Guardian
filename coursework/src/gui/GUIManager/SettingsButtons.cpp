// ReSharper disable CppIncompleteSwitchStatement CppDefaultCaseNotHandledInSwitchStatement CppClangTidyClangDiagnosticSwitch CppClangTidyHicppMultiwayPathsCovered CppClangTidyClangDiagnosticSwitchEnum
#include "../../../include/gui/GUIManager/SettingsButtons.hpp"

SettingsButtons::Strings SettingsButtons::getActionNames() const {
    return {_control->forward_move.toString(), _control->backward_move.toString(),
        _control->left_move.toString(), _control->right_move.toString(), _control->take_collectible.toString(),
        _control->fire.toString()};
}

SettingsButtons::SettingsButtons(Control& control, const sf::Font& font, const sf::Color pressed_color):
    _control(&control), _buttons(font), _pressed_color(pressed_color) { }

void SettingsButtons::setActionNames() {
    const std::vector names(getActionNames());

    int i = 0;
    for (const auto& name : names) {
        _buttons.setStr(i, name);
        ++i;
    }
}

void SettingsButtons::setInputData(const InputData& input_data) {
    _buttons.setStr(_active_index, input_data.toString());
    switch (_active_index) {
    case 0:
        _control->forward_move = input_data;
        break;
    case 1:
        _control->backward_move = input_data;
        break;
    case 2:
        _control->left_move = input_data;
        break;
    case 3:
        _control->right_move = input_data;
        break;
    case 4:
        _control->take_collectible = input_data;
        break;
    case 5:
        _control->fire = input_data;
        break;
    }
    _active_index = -1;
}

void SettingsButtons::createButtons(bool& continue_settings, const ButtonColors &button_colors) {
    const std::vector names(getActionNames());
    int i = 0;
    
    for (const auto& name : names) {
        _buttons.addButton(name, [this, i]{_active_index = i;}, button_colors);
        ++i;
    }
    _buttons.addButtonWidthOriginCenter("Return", [&continue_settings]{continue_settings = false;}, button_colors);
}

void SettingsButtons::draw(sf::RenderWindow &render_window) {
    if (hasActiveButton()) {
        const auto prev_color = _buttons.getColor(_active_index);
        _buttons.setColor(_active_index, _pressed_color);
        _buttons.draw(render_window);
        _buttons.setColor(_active_index, prev_color);
    }
    else
        _buttons.draw(render_window);
}

void SettingsButtons::resetActiveIndex() { _active_index = -1; }

void SettingsButtons::setDefaultColor() { _buttons.setDefaultColor(); }

bool SettingsButtons::handleClick(const sf::Vector2f& mouse) const { return _buttons.handleClick(mouse); }

void SettingsButtons::setPos(const size_t i, const sf::Vector2f& p) { _buttons.setPos(i, p); }

bool SettingsButtons::hasActiveButton() const { return _active_index != -1; }

MouseMovedRes SettingsButtons::handleHoverTextColors(const sf::Vector2f& position) {
    return _buttons.handleHoverTextColors(position);
}