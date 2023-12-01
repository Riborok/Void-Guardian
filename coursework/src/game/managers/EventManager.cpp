// ReSharper disable CppDefaultCaseNotHandledInSwitchStatement CppIncompleteSwitchStatement CppClangTidyClangDiagnosticSwitch
#include <SFML/Window/Event.hpp>

#include "../../../include/game/managers/EventManager.hpp"

EventManager::EventManager(sf::RenderWindow& window, InputHandler& input_handler, HotkeyManager& hotkey_manager,
                           GameLoopState& game_loop_state, WindowParam& window_param)
    : _window(&window), _input_handler(&input_handler), _game_loop_state(&game_loop_state),
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
            _input_handler->clear();
            _game_loop_state->changeActivity();
            break;
        case sf::Event::GainedFocus:
            _game_loop_state->changeActivity();
            break;
        case sf::Event::MouseButtonPressed:
            _input_handler->handleMouseDown(event.mouseButton.button);
            break;
        case sf::Event::MouseButtonReleased:
            _input_handler->handleMouseUp(event.mouseButton.button);
            break;
        case sf::Event::KeyPressed: {
                const sf::Keyboard::Key key_code = event.key.code;
                _input_handler->handleKeyDown(key_code);
                analyzeHotkeyResult(_hotkey_manager->handleHotkeys(key_code));
                break;
        }
        case sf::Event::KeyReleased: {
                _input_handler->handleKeyUp(event.key.code);
                break;
        }
        }
    }
}