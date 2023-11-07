// ReSharper disable CppDefaultCaseNotHandledInSwitchStatement CppIncompleteSwitchStatement CppClangTidyClangDiagnosticSwitch
#include <SFML/Window/Event.hpp>

#include "../../../include/game/managers/EventManager.hpp"

EventManager::EventManager(sf::RenderWindow& window, KeyHandler& key_handler, HotkeyManager& hotkey_manager,
                           GameLoopState& game_loop_state, sf::Vector2f& window_half_size)
    : _window(&window), _key_handler(&key_handler), _game_loop_state(&game_loop_state),
      _hotkey_manager(&hotkey_manager), _window_half_size(&window_half_size) {}

void EventManager::setNewWindowSize() const {
    *_window_half_size = static_cast<sf::Vector2f>(_window->getSize()) / 2.0f;
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
            _key_handler->clearKeys();
            _game_loop_state->changeActivity();
            break;
        case sf::Event::GainedFocus:
            _game_loop_state->changeActivity();
            break;
        case sf::Event::KeyPressed: {
                const sf::Keyboard::Key key_code = event.key.code;
                _key_handler->handleKeyDown(key_code);
                analyzeHotkeyResult(_hotkey_manager->handleHotkeys(key_code));
                break;
        }
        case sf::Event::KeyReleased: {
                _key_handler->handleKeyUp(event.key.code);
                break;
        }
        }
    }
}