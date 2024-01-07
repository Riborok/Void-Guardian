// ReSharper disable CppDefaultCaseNotHandledInSwitchStatement CppIncompleteSwitchStatement CppClangTidyClangDiagnosticSwitch
#include <SFML/Window/Event.hpp>

#include "../../../include/game/managers/EventManager.hpp"

EventManager::EventManager(sf::RenderWindow& window, HotkeyManager& hotkey_manager,
                           GameLoopState& game_loop_state, WindowParam& window_param)
    : _window(&window), _game_loop_state(&game_loop_state),
      _hotkey_manager(&hotkey_manager), _window_param(&window_param) {}

void EventManager::setNewWindowSize() const {
    _window_param->updateSize(static_cast<sf::Vector2f>(_window->getSize()));
}

void EventManager::analyzeHotkeyResult(const HotkeyManagerResult result) const {
    switch (result) {
    case HotkeyManagerResult::TOGGLE_FULLSCREEN:
        setNewWindowSize();
        break;
    }
}

void EventManager::processEvents() const {
    sf::Event event;
    while (_window->pollEvent(event)) {
        switch (event.type) {
        case sf::Event::Closed:
            _window->close();
            break;
        case sf::Event::Resized:
            setNewWindowSize();
            break;
        case sf::Event::LostFocus:
        case sf::Event::GainedFocus:
            _game_loop_state->changeActivity();
            break;
        case sf::Event::KeyPressed: 
            analyzeHotkeyResult(_hotkey_manager->handleHotkeys(event.key.code));
            break;
        }
    }
}