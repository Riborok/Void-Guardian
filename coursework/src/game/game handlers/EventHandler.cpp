// ReSharper disable CppDefaultCaseNotHandledInSwitchStatement CppIncompleteSwitchStatement CppClangTidyClangDiagnosticSwitch
#include <SFML/Window/Event.hpp>

#include "../../../include/game/game handlers/EventHandler.hpp"

EventHandler::EventHandler(sf::RenderWindow& window, GameLoopState &game_loop_state,
                           SetNewWindowSize &&set_new_window_size, FullscreenToggler &fullscreen_toggler,
                           const sf::Cursor &cursor, SetPause &&set_pause):
    _window(&window), _game_loop_state(&game_loop_state), _set_new_window_size(std::move(set_new_window_size)),
    _hotkey_handler(FunctionCreator::createToggleFullscreen(fullscreen_toggler, cursor, _set_new_window_size),
        std::move(set_pause)) {}

void EventHandler::handleEvents() const {
    sf::Event event;
    while (_window->pollEvent(event)) {
        switch (event.type) {
        case sf::Event::Closed:
            _window->close();
            break;
        case sf::Event::Resized:
            _set_new_window_size();
            break;
        case sf::Event::LostFocus:
            _game_loop_state->is_active = false;
            break;
        case sf::Event::GainedFocus:
            _game_loop_state->is_active = true;
            _game_loop_state->clock.restart();
            break;
        case sf::Event::KeyPressed: 
            _hotkey_handler.handleHotkeys(event.key.code);
            break;
        }
    }
}