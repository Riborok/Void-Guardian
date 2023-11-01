#pragma once

#include "../Quadtree/Quadtree.h"
#include "construction/CreatingRectangularLocation.h"
#include "executors/PlayerExecutor.h"
#include "executors/SpriteStateExecutor.h"
#include "processors/SpriteDrawer.h"
#include "input/KeyHandler.h"
#include "processors/game loop/GameLoop.h"

class GameMaster final {
    static constexpr float QUADTREE_SIZE = 3840;

    sf::RenderWindow *_window;
    std::unordered_set<Element*, IdentifiableHash> _elements;
    HotkeyManager _hotkey_manager;
    KeyHandler _key_handler;
    Quadtree _quadtree;
    SpriteStateExecutor *_sprite_state_executor; 
    PlayerExecutor *_player_manager;
    GameLoop _game_loop;
public:
    explicit GameMaster(sf::RenderWindow &window) :
            _window(&window),
            _hotkey_manager(FullscreenToggler(window, false)),
            _quadtree(-QUADTREE_SIZE, -QUADTREE_SIZE, QUADTREE_SIZE, QUADTREE_SIZE),
            _sprite_state_executor(new SpriteStateExecutor(_elements, _quadtree)), // Memory will be released by class Render
            _player_manager(new PlayerExecutor(window, _key_handler)),  // Memory will be released by class Render
            _game_loop(window, _key_handler, _hotkey_manager, _elements) {
        _game_loop.registerExecutor(_sprite_state_executor);
        _game_loop.registerExecutor(_player_manager);

        auto *player_element = ElementCreation::create({0, 0}, 0, Types::WRAITH, 0, 0.3f);
        _quadtree.insert(player_element);
        
        _player_manager->addPlayer(new Player(
            *player_element,
            {sf::Keyboard::W, sf::Keyboard::Space},
            0.2f)
        );
        
        //
        CreatingRectangularLocation::createBackground(0, {0, 0}, {1920, 1024}, _quadtree, 1.0f);
        //
    }
    
    void start() {
        while (_window->isOpen()) {
            const auto size = static_cast<sf::Vector2f>(_window->getSize());
            Rectangle rect({size.x / 2, size.y / 2},{size.x / 2, size.y / 2});
            _quadtree.getCollisions(rect, _elements);
            
            _game_loop.nextIteration();
        }   
    }
    
    ~GameMaster() noexcept = default;
    
    GameMaster(const GameMaster&) noexcept = delete;
    GameMaster& operator=(const GameMaster&) noexcept = delete;
    GameMaster(GameMaster&&) noexcept = delete;
    GameMaster& operator=(GameMaster&&) noexcept = delete;
};
