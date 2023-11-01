#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "../input/HotkeyManager.h"
#include "../input/KeyHandler.h"
#include "../processors/game loop/GameLoopState.h"

class EventManager final {
    sf::RenderWindow *_window;
    KeyHandler *_key_handler;
    GameLoopState *_game_loop_state;
    HotkeyManager *_hotkey_manager;
public:
    EventManager(sf::RenderWindow &window, KeyHandler &key_handler, HotkeyManager &hotkey_manager, GameLoopState &game_loop_state):
        _window(&window), _key_handler(&key_handler), _game_loop_state(&game_loop_state), _hotkey_manager(&hotkey_manager) { }
    void processEvents() const {
        sf::Event event;
        while (_window->pollEvent(event)) {
            // ReSharper disable once CppDefaultCaseNotHandledInSwitchStatement CppIncompleteSwitchStatement
            switch (event.type) {  // NOLINT(clang-diagnostic-switch) 
            case sf::Event::Closed:
                _window->close();
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
                    _hotkey_manager->handleHotkeys(key_code);
                    _key_handler->handleKeyDown(key_code);
                    break;
                }
            case sf::Event::KeyReleased: {
                    _key_handler->handleKeyUp(event.key.code);
                    break;
                }
            }
        }
    }

    ~EventManager() noexcept = default;
    
    EventManager(const EventManager&) noexcept = delete;
    EventManager& operator=(const EventManager&) noexcept = delete;
    EventManager(EventManager&&) noexcept = delete;
    EventManager& operator=(EventManager&&) noexcept = delete;
};
