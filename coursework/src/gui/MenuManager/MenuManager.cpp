// ReSharper disable CppIncompleteSwitchStatement CppDefaultCaseNotHandledInSwitchStatement CppClangTidyClangDiagnosticSwitch
#include <SFML/Window/Event.hpp>
#include "../../../include/gui/MenuManager/MenuManager.hpp"
#include "../../../include/additionally/AdditionalFunc.hpp"
#include "../../../include/additionally/PixelConverter.hpp"

MenuManager::MenuManager(GameSetup &game_setup, MenuManagerInfo &&menu_manager_info,
                         const Cursors &cursors, const Colors &colors):
        _game_context(&game_setup.game_context), _menu_manager_info(std::move(menu_manager_info)),
        _buttons(*_menu_manager_info.game_name.getFont()), _cursors(&cursors), _background_color(colors.background_color){
    createMenu(colors.button_colors, game_setup.gui_manager.settings_manager);
    setButtonPos();
}

void MenuManager::setButtonPos() {
    const auto window_size = _game_context->window.getSize();
    const float x_center = static_cast<float>(window_size.x) / 2.0f;
    const float y_start = static_cast<float>(window_size.y) / 10.0f;
    const float button_spacing(PixelConverter::convertHeightToCurrentScreen(BUTTON_SPACING));
    
    _menu_manager_info.game_name.setPosition({x_center, y_start});
    
    const size_t count = _buttons.getCount();
    float curr_y = y_start + button_spacing * 2;
    for (size_t i = 0; i < count; ++i) {
        _buttons.setPos(i, {x_center, curr_y});
        curr_y += button_spacing;
    }
}

void MenuManager::createMenu(const ButtonColors& button_colors, SettingsManager &settings_manager) {
    auto& game_name = _menu_manager_info.game_name;
    const auto bounds = game_name.getGlobalBounds();
    game_name.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
    game_name.setFillColor(button_colors.text_color);
    
    _buttons.addButtonWidthOriginCenter("START", [this]{_continue_menu = false;}, button_colors);
    _buttons.addButtonWidthOriginCenter("SETTINGS", [&settings_manager]{settings_manager.startSettings();}, button_colors);
    _buttons.addButtonWidthOriginCenter("ABOUT",[this] {AdditionalFunc::openUrl(_menu_manager_info.about_url);}, button_colors);
    _buttons.addButtonWidthOriginCenter("EXIT", [this]{_game_context->window.close();}, button_colors);
}

void MenuManager::drawMenu() const {
    auto& window = _game_context->window;
    window.clear(_background_color);
    window.draw(_menu_manager_info.game_name);
    _buttons.draw(window);
    window.display();
}

void MenuManager::processKeyPressed(const sf::Keyboard::Key key) const {
    switch (key) {
    case FullscreenToggler::DEFAULT_KEYBOARD_SWITCH:
        _game_context->fullscreen_toggler.toggleFullscreen(_cursors->normal_cursor);
        break;
    }
}

void MenuManager::processEvents() {
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
            if (event.mouseButton.button == sf::Mouse::Left)
                _buttons.handleClick(window.mapPixelToCoords(sf::Mouse::getPosition(window)));    
            break;
        case sf::Event::MouseMoved:
            const auto buttons_res(_buttons.handleHoverTextColors(window.mapPixelToCoords(sf::Mouse::getPosition(window))));

            if (has(buttons_res, MouseMovedRes::REDRAW))
                drawMenu();

            if (has(buttons_res, MouseMovedRes::SELECTION_CURSOR))
                window.setMouseCursor(_cursors->selection_cursor);
            else
                window.setMouseCursor(_cursors->normal_cursor);
            break;
        }
    }
}

void MenuManager::setDefaultTitle() const {
    _game_context->window.setTitle(_game_context->fullscreen_toggler.getTitle());
}

void MenuManager::startMenu() {
    AdditionalFunc::setDefaultView(_game_context->window);
    setDefaultTitle();
    _buttons.setDefaultColor();
    drawMenu();
    
    _continue_menu = true;
    while (_continue_menu && _game_context->window.isOpen()) {
        processEvents();
    }
}