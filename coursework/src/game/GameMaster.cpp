#include "../../include/game/GameMaster.hpp"

#include "../../include/element/ElementCreation.hpp"
#include "../../include/game/construction/RoomCreator.hpp"
#include "../../include/game/construction/MapCreation/GameFieldCreator.hpp"
#include "../../include/game/executors/SpriteStateExecutor.hpp"

GameField createGameField() {
    const GameFieldCreator game_field_creator;
    return game_field_creator.create(0, 0);
}

Player* createPlayer(const sf::Vector2f &p0) {
    auto *player_element = ElementCreation::createReplaceable(p0, 0,
        ElementTypes::WRAITH, 0, {WRAITH_SCALE, WRAITH_SCALE});
    
    return new Player(
        *player_element,
        {sf::Keyboard::W, sf::Keyboard::Space},
        WRAITH_SPEED);
}

GameMaster::GameMaster(sf::RenderWindow &window) :
        _window(&window),
        _game_field(createGameField()),
        _player(createPlayer(_game_field.start)),
        _hotkey_manager(FullscreenToggler(window, false)),
        _key_handler(),
        _game_updater(_player->getElement().getPolygon(), window, _game_field.quadtree_el),
        _game_loop(window, _key_handler, _hotkey_manager, _game_updater){
    // Memory will be released by class Render
    auto *sprite_executor = new SpriteStateExecutor(_game_updater);
    // Memory will be released by class Render
    auto *player_executor = new PlayerExecutor(window, _key_handler, _game_field.quadtree_el);
    
    _game_loop.registerExecutor(sprite_executor);
    _game_loop.registerExecutor(player_executor);
    
    player_executor->addPlayer(_player);
    _game_field.quadtree_el.insert(&_player->getElement());
}

void GameMaster::start() {
    while (_window->isOpen()) {
        _game_loop.nextIteration();
    }
}
