// ReSharper disable CppIncompleteSwitchStatement CppDefaultCaseNotHandledInSwitchStatement CppClangTidyClangDiagnosticSwitch
#include <cstdlib>
#include <SFML/Window/Event.hpp>
#include "../../include/gui/MenuManager.hpp"
#include "../../include/initialization/GameDataInitialization.hpp"

MenuManager::MenuManager(sf::RenderWindow &window, FullscreenToggler &fullscreen_toggler,
        PlayerProgress &player_progress, Control &control, const std::string &font_src):
        _window(&window), _fullscreen_toggler(&fullscreen_toggler), _buttons(_font),
        _game_name(fullscreen_toggler.getTitle(), _font, GAME_NAME_SIZE), _player_progress(&player_progress),
        _control(&control){
    _font.loadFromFile(font_src);
    createMenu();
}

void MenuManager::setButtonPos() {
    const float x_center = static_cast<float>(_window->getSize().x) / 2.0f;
    const float y_start = static_cast<float>(_window->getSize().y) / 10.0f;
    
    _game_name.setPosition({x_center, y_start});
    _buttons.setPos(0, {x_center, y_start + 200});
    _buttons.setPos(1, {x_center, y_start + 300});
    _buttons.setPos(2, {x_center, y_start + 400});
    _buttons.setPos(3, {x_center, y_start + 500});
}

void MenuManager::createMenu() {
    _game_name.setOrigin(_game_name.getGlobalBounds().width / 2.0f, _game_name.getGlobalBounds().height / 2.0f);
    
    _buttons.addButton("START", [&]{_continue_menu = false;});
    _buttons.addButton("SETTINGS", [&]{});
    _buttons.addButton("ABOUT",[] {
        #ifdef _WIN32
            auto command = "start";
        #elif __APPLE__
            auto command = "open";
        #else
            auto command = "xdg-open";
        #endif
        const std::string full_command = std::string(command).append(" https://github.com/Riborok/Void-Guardian");
        system(full_command.c_str());
    });
    _buttons.addButton("EXIT", [&]{_window->close();});
}

void MenuManager::drawMenu() const {
    _window->clear(sf::Color::Black);
    _window->draw(_game_name);
    _buttons.draw(*_window);
    _window->display();
}

void MenuManager::processKeyPressed(const sf::Keyboard::Key& key) const {
    switch (key) {
    case sf::Keyboard::F11:
        _fullscreen_toggler->toggleFullscreen();
        break;
    }
}

void MenuManager::processEvents() {
    sf::Event event;
    while (_window->pollEvent(event)) {
        switch (event.type) {
        case sf::Event::Closed:
            _window->close();
            break;
        case sf::Event::KeyPressed:
            processKeyPressed(event.key.code);
        case sf::Event::MouseButtonPressed:
            if (event.mouseButton.button == sf::Mouse::Left)
                _buttons.checkClick(_window->mapPixelToCoords(sf::Mouse::getPosition(*_window)));    
            break;
        case sf::Event::MouseMoved:
            _buttons.setColors(_window->mapPixelToCoords(sf::Mouse::getPosition(*_window)));
            drawMenu();
            break;
        }
    }
}

void MenuManager::startMenu() {
    _fullscreen_toggler->recreateWindow();
    _continue_menu = true;
    setButtonPos();
    drawMenu();
    while (_continue_menu && _window->isOpen()) {
        processEvents();
    }
}