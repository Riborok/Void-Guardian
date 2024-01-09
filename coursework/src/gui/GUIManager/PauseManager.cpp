// ReSharper disable CppIncompleteSwitchStatement CppDefaultCaseNotHandledInSwitchStatement CppClangTidyClangDiagnosticSwitch
#include <SFML/Window/Event.hpp>
#include "../../../include/gui/GUIManager/PauseManager.hpp"
#include "../../../include/additionally/AdditionalFunc.hpp"
#include "../../../include/additionally/PixelConverter.hpp"

void PauseManager::setButtonPos() {
    const auto window_size = _window->getSize();
    const float x_center = static_cast<float>(window_size.x) / 2.0f;
    const float y_start = static_cast<float>(window_size.y) / 10.0f;
    const float button_spacing(PixelConverter::convertHeightToCurrentScreen(BUTTON_SPACING));
    
    const size_t count = _buttons.getCount();
    float curr_y = y_start + button_spacing * 2;
    for (size_t i = 0; i < count; ++i) {
        _buttons.setPos(i, {x_center, curr_y});
        curr_y += button_spacing;
    }
}

void PauseManager::createMenu(const ButtonColors& button_colors, SettingsManager &settings_manager) {
    _buttons.addButtonWidthOriginCenter("CONTINUE", [this]{_game_state = nullptr;}, button_colors);
    _buttons.addButtonWidthOriginCenter("SETTINGS", [&settings_manager]{settings_manager.startSettings();}, button_colors);
    _buttons.addButtonWidthOriginCenter("MENU", [this]{*_game_state = GameState::RETURN_TO_MENU; _game_state = nullptr; }, button_colors);
    _buttons.addButtonWidthOriginCenter("EXIT", [this]{_window->close();}, button_colors);
}

void PauseManager::drawPauseMenu() const {
    _window->clear(_background_color);
    _buttons.draw(*_window);
    _window->display();
}

void PauseManager::processKeyPressed(const sf::Keyboard::Key key) {
    switch (key) {
    case FullscreenToggler::DEFAULT_KEYBOARD_SWITCH:
        _fullscreen_toggler->toggleFullscreen(_cursors->normal_cursor);
        break;
    case sf::Keyboard::Escape:
        _game_state = nullptr;
        break;
    }
}

void PauseManager::processEvents() {
    sf::Event event;
    while (_window->pollEvent(event)) {
        switch (event.type) {
        case sf::Event::Closed:
            _window->close();
            break;
        case sf::Event::KeyPressed:
            processKeyPressed(event.key.code);
            break;
        case sf::Event::MouseButtonReleased:
            if (event.mouseButton.button == sf::Mouse::Left)
                _buttons.handleClick(_window->mapPixelToCoords(sf::Mouse::getPosition(*_window)));    
            break;
        case sf::Event::MouseMoved:
            const auto buttons_res(_buttons.handleHoverTextColors(_window->mapPixelToCoords(sf::Mouse::getPosition(*_window))));

            if (has(buttons_res, MouseMovedRes::REDRAW))
                drawPauseMenu();

            if (has(buttons_res, MouseMovedRes::SELECTION_CURSOR))
                _window->setMouseCursor(_cursors->selection_cursor);
            else
                _window->setMouseCursor(_cursors->normal_cursor);
            break;
        }
    }
}

PauseManager::PauseManager(GameContext &game_context, SettingsManager &settings_manager, const sf::Font& font, const Cursors& cursors, const Colors& colors):
        _window(&game_context.window), _fullscreen_toggler(&game_context.fullscreen_toggler),
        _buttons(font), _cursors(&cursors), _background_color(colors.background_color){
    createMenu(colors.button_colors, settings_manager);
    setButtonPos();
}

void PauseManager::startPauseMenu(GameState& game_state) {
    _game_state = &game_state;
    AdditionalFunc::setDefaultView(*_window);
    _buttons.setDefaultColor();
    drawPauseMenu();
    
    while (_game_state && _window->isOpen()) {
        processEvents();
    }
}
