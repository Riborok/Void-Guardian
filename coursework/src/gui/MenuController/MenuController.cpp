// ReSharper disable CppIncompleteSwitchStatement CppDefaultCaseNotHandledInSwitchStatement CppClangTidyClangDiagnosticSwitch
#include <SFML/Window/Event.hpp>
#include "../../../include/gui/MenuController/MenuController.hpp"
#include "../../../include/additionally/AdditionalFunc.hpp"
#include "../../../include/additionally/PixelConverter.hpp"
#include "../../../include/gui/ReservedKeys.hpp"

MenuController::MenuController(GameSetup &game_setup, const sf::Font &font, const std::string &title, std::string &&about_url,
                         const Cursors &cursors, const Colors &colors):
        _game_context(&game_setup.game_context), _menu_controller_info(font, title, std::move(about_url)),
        _buttons(font), _cursors(&cursors), _background_color(colors.background_color){
    createMenu(colors.button_colors, game_setup.ui_controller.settings_controller);
    setButtonPos();
}

void MenuController::setButtonPos() {
    const auto window_size = _game_context->window.getSize();
    const float x_center = static_cast<float>(window_size.x) / 2.0f;
    const float y_start = static_cast<float>(window_size.y) / 10.0f;
    const float button_spacing(PixelConverter::convertHeightToCurrentScreen(BUTTON_SPACING));
    
    _menu_controller_info.game_name.setPosition({x_center, y_start});
    
    const size_t count = _buttons.getCount();
    float curr_y = y_start + button_spacing * 2;
    for (size_t i = 0; i < count; ++i) {
        _buttons.setPos(i, {x_center, curr_y});
        curr_y += button_spacing;
    }
}

void MenuController::createMenu(const ButtonColors& button_colors, SettingsController &settings_controller) {
    auto& game_name = _menu_controller_info.game_name;
    const auto bounds = game_name.getGlobalBounds();
    game_name.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
    game_name.setFillColor(button_colors.text_color);
    
    _buttons.addButtonWidthOriginCenter("START", [this]{_continue_menu = false;}, button_colors);
    _buttons.addButtonWidthOriginCenter("SETTINGS", [&settings_controller, this] {
        settings_controller.startSettings();
        _buttons.setDefaultColor();
        drawMenu();
    }, button_colors);
    _buttons.addButtonWidthOriginCenter("ABOUT",[this] {AdditionalFunc::openUrl(_menu_controller_info.about_url);}, button_colors);
    _buttons.addButtonWidthOriginCenter("EXIT", [this]{_game_context->window.close();}, button_colors);
}

void MenuController::drawMenu() const {
    auto& window = _game_context->window;
    window.clear(_background_color);
    window.draw(_menu_controller_info.game_name);
    _buttons.draw(window);
    window.display();
}

void MenuController::handleKeyPressed(const sf::Keyboard::Key key) const {
    switch (key) {
    case ReservedKeys::FULL_SCREEN_TOGGLE:
        _game_context->fullscreen_toggler.toggleFullscreen(_cursors->normal_cursor);
        drawMenu();
        break;
    }
}

void MenuController::handleEvents() {
    auto& window = _game_context->window;
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::KeyPressed:
            handleKeyPressed(event.key.code);
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

void MenuController::setDefaultTitle() const {
    _game_context->window.setTitle(_game_context->fullscreen_toggler.getTitle());
}

void MenuController::startMenu() {
    AdditionalFunc::setDefaultView(_game_context->window);
    setDefaultTitle();
    _buttons.setDefaultColor();
    drawMenu();
    
    _continue_menu = true;
    while (_continue_menu && _game_context->window.isOpen()) {
        handleEvents();
    }
}