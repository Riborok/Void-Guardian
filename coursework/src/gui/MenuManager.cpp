// ReSharper disable CppIncompleteSwitchStatement CppDefaultCaseNotHandledInSwitchStatement CppClangTidyClangDiagnosticSwitch
#include <SFML/Window/Event.hpp>
#include "../../include/gui/MenuManager.hpp"

#include "../../include/additionally/AdditionalFunc.hpp"

MenuManager::MenuManager(GameContext &game_context, MenuManagerInfo &&menu_manager_info):
        _game_context(&game_context), _menu_manager_info(std::move(menu_manager_info)),
        _buttons(_menu_manager_info.font){
    createMenu();
    setButtonPos();
}

void MenuManager::setButtonPos() {
    const float x_center = static_cast<float>(_game_context->window.getSize().x) / 2.0f;
    const float y_start = static_cast<float>(_game_context->window.getSize().y) / 10.0f;
    
    _menu_manager_info.game_name.setPosition({x_center, y_start});
    _buttons.setPos(0, {x_center, y_start + 200});
    _buttons.setPos(1, {x_center, y_start + 300});
    _buttons.setPos(2, {x_center, y_start + 400});
    _buttons.setPos(3, {x_center, y_start + 500});
}

void MenuManager::createMenu() {
    auto& game_name = _menu_manager_info.game_name;
    game_name.setOrigin(game_name.getGlobalBounds().width / 2.0f, game_name.getGlobalBounds().height / 2.0f);
    
    _buttons.addButton("START", [&]{_continue_menu = false;});
    _buttons.addButton("SETTINGS", [&]{});
    _buttons.addButton("ABOUT",[&] {AdditionalFunc::openUrl(_menu_manager_info.about_url);});
    _buttons.addButton("EXIT", [&]{_game_context->window.close();});
}

void MenuManager::drawMenu() const {
    auto& window = _game_context->window;
    window.clear(sf::Color::Black);
    window.draw(_menu_manager_info.game_name);
    _buttons.draw(window);
    window.display();
}

void MenuManager::processKeyPressed(const sf::Keyboard::Key& key) const {
    switch (key) {
    case sf::Keyboard::F11:
        _game_context->fullscreen_toggler.toggleFullscreen();
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
        case sf::Event::MouseButtonPressed:
            if (event.mouseButton.button == sf::Mouse::Left)
                _buttons.handleClick(window.mapPixelToCoords(sf::Mouse::getPosition(window)));    
            break;
        case sf::Event::MouseMoved:
            const auto buttons_res(_buttons.handleHoverTextColors(window.mapPixelToCoords(sf::Mouse::getPosition(window))));

            if (has(buttons_res, MouseMovedRes::REDRAW))
                drawMenu();

            if (has(buttons_res, MouseMovedRes::SELECTION_CURSOR))
                window.setMouseCursor(_cursors.selection_cursor);
            else
                window.setMouseCursor(_cursors.normal_cursor);
            break;
        }
    }
}

void MenuManager::setDefaultTitle() const {
    _game_context->window.setTitle(_game_context->fullscreen_toggler.getTitle());
}

void MenuManager::setDefaultView() const {
    auto& window = _game_context->window;
    window.setView(window.getDefaultView());
}

void MenuManager::startMenu() {
    setDefaultView();
    setDefaultTitle();
    drawMenu();
    
    _continue_menu = true;
    while (_continue_menu && _game_context->window.isOpen()) {
        processEvents();
    }
}