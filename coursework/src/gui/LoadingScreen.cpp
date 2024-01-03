// ReSharper disable CppIncompleteSwitchStatement CppDefaultCaseNotHandledInSwitchStatement CppClangTidyClangDiagnosticSwitch CppTooWideScopeInitStatement CppTooWideScope
#include <stdexcept>
#include <chrono>
#include <thread>
#include "../../include/gui/LoadingScreen.hpp"

void LoadingScreen::createText(const sf::Color color) {
    const auto window_size = _window->getSize();
    const auto x_center = static_cast<float>(window_size.x) / 2.0f;
    const auto y_start = static_cast<float>(window_size.y) / 2.0f;
    _loading_screen_info.text.setPosition({x_center, y_start});
    _loading_screen_info.text.setFillColor(color);
}

void LoadingScreen::setTextBounds() {
    const auto bounds = _loading_screen_info.text.getGlobalBounds();
    _loading_screen_info.text.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
}

void LoadingScreen::processKeyPressed(const sf::Keyboard::Key& key) const {
    switch (key) {
    case sf::Keyboard::F11:
        _fullscreen_toggler->toggleFullscreen();
        break;
    }
}

void LoadingScreen::processEvents() const {
    sf::Event event;
    while (_window->pollEvent(event)) {
        switch (event.type) {
        case sf::Event::Closed:
            _window->close();
            break;
        case sf::Event::KeyPressed:
            processKeyPressed(event.key.code);
            break;
        }
    }
}

void LoadingScreen::redraw() const {
    _window->clear(_background_color);
    _window->draw(_loading_screen_info.text);
    _window->display();
}

void LoadingScreen::updateText() {
    if (_clock.getElapsedTime().asMilliseconds() >= UPDATE_TIME) {
        _clock.restart();
        if (++_loading_screen_info.pointer >= _loading_screen_info.strings.size()) { _loading_screen_info.pointer = 0; }
        setTextStr();
        setTextBounds();
        redraw();
    }
}

LoadingScreen::LoadingScreen(sf::RenderWindow& window, FullscreenToggler &fullscreen_toggler,
            LoadingScreenInfo&& loading_screen_info, const Colors &colors): _window(&window),
            _fullscreen_toggler(&fullscreen_toggler), _loading_screen_info(std::move(loading_screen_info)),
            _background_color(colors.background_color) {
    _cursor.loadFromSystem(sf::Cursor::Arrow);
    setTextBounds();   
    createText(colors.text_color);
}

void LoadingScreen::setWindowParameters() const {
    _window->setMouseCursor(_cursor);
    _window->setView(_window->getDefaultView());
}

void LoadingScreen::restoreSettings() {
    _continue_screen = true;
    _loading_screen_info.pointer = 0;
    setTextStr();
    _clock.restart();
}

void LoadingScreen::setTextStr() {
    _loading_screen_info.text.setString(_loading_screen_info.strings[_loading_screen_info.pointer]);
}

void LoadingScreen::start() {
    setWindowParameters();
    restoreSettings();
    redraw();
    
    while (_window->isOpen() && _continue_screen) {
        processEvents();
        updateText();
    }
}

void LoadingScreen::end() {
    static constexpr size_t WAIT_DELAY = 42;
    static constexpr int MAX_ATTEMPTS = 42;
    int attempts = 0;
    while (!_continue_screen) {
        std::this_thread::sleep_for(std::chrono::milliseconds(WAIT_DELAY));
        #ifndef NDEBUG
        if (++attempts >= MAX_ATTEMPTS)
            throw std::runtime_error("Exceeded maximum attempts in LoadingScreen::end()");
        #endif
    }
    _continue_screen = false;
}