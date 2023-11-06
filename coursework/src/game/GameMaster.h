#pragma once

#include "../Quadtree/Quadtree.h"
#include "construction/MapCreation.h"
#include "construction/RectLoc.h"
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
    Quadtree<Element> _quadtree;
    Quadtree<RectLoc> _rect_locs;
    GameLoop _game_loop;

    Polygon *_focus;
    sf::Vector2f _window_half_size;
    sf::Vector2f _offset;

    void setParameters() {
        const auto focus = _focus->calcCenter();
        _offset = _window_half_size - focus;
        
        _elements.clear();
        Rectangle rect(focus, _window_half_size);
        _quadtree.getCollisions(rect, _elements);
    }
public:
    void addPlayer(PlayerExecutor *player_executor) {
        auto *player_element = ElementCreation::createReplaceable(_window_half_size, 0, Types::ElementTypes::WRAITH, 0, {0.3f, 0.3f});
        _quadtree.insert(player_element);
        
        player_executor->addPlayer(new Player(
            *player_element,
            {sf::Keyboard::W, sf::Keyboard::Space},
            0.2f)
        );
        _focus = &player_element->getPolygon();
    }
    explicit GameMaster(sf::RenderWindow &window) :
            _window(&window),
            _hotkey_manager(FullscreenToggler(window, false)),
            _quadtree(-QUADTREE_SIZE, -QUADTREE_SIZE, QUADTREE_SIZE, QUADTREE_SIZE),
            _rect_locs(-QUADTREE_SIZE, -QUADTREE_SIZE, QUADTREE_SIZE, QUADTREE_SIZE),
            _game_loop(window, _key_handler, _hotkey_manager, _elements, _window_half_size, _offset),
            _window_half_size(static_cast<sf::Vector2f>(window.getSize()) / 2.0f){

        auto *sprite_executor(new SpriteStateExecutor(_elements, _quadtree)); // Memory will be released by class Render
        _game_loop.registerExecutor(sprite_executor); 
        auto *player_executor = new PlayerExecutor(_quadtree, _key_handler); // Memory will be released by class Render
        _game_loop.registerExecutor(player_executor);
        addPlayer(player_executor);
        
        //
        MapCreation::createBackground(0, {0, 0}, 15, 8, _quadtree, {1.0f, 1.0f});
        _rect_locs.insert(createRectLoc(0, {0, 0}, 15, 8, {1.0f, 1.0f},
            MapCreation::DoorOpening::TOP | MapCreation::DoorOpening::LEFT,
            _quadtree, 4, 4));
        //
    }
    
    void start() {
        while (_window->isOpen()) {
            setParameters();
            _game_loop.nextIteration();
        }   
    }
    
    ~GameMaster() noexcept = default;
    
    GameMaster(const GameMaster&) noexcept = delete;
    GameMaster& operator=(const GameMaster&) noexcept = delete;
    GameMaster(GameMaster&&) noexcept = delete;
    GameMaster& operator=(GameMaster&&) noexcept = delete;
};
