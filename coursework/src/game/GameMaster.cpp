#include "../../include/game/GameMaster.hpp"

#include "../../include/game/construction/RoomCreator.hpp"
#include "../../include/game/construction/MapCreation/GameFieldCreator.hpp"
#include "../../include/game/executors/SpriteStateExecutor.hpp"

GameField createGameField(const GameData &game_data, ElementCreator &element_creator, LocationCreator &location_creator) {
    const GameFieldCreator game_field_creator(game_data.latest_map_index);
    return game_field_creator.create(game_data.background_data, game_data.boundary_data,
        element_creator, location_creator);
}

Player* createPlayer(const sf::Vector2f &p0, ElementCreator &element_creator, const PlayerInfo &player_info) {
    auto *player_element = element_creator.createReplaceable({p0, 0,
        ElementType::WRAITH, 0, player_info.scale});
    
    return new Player(
        *player_element,
        {sf::Keyboard::W, sf::Keyboard::Space},
        player_info.speed);
}

GameMaster::GameMaster(sf::RenderWindow &window, GameData &&game_data) :
        _element_creator(std::move(game_data.simple_sprite_infos), std::move(game_data.animated_sprite_infos)),
        _window(&window),
        _game_field(createGameField(game_data, _element_creator, _location_creator)),
        _collision_manager(std::move(game_data.collision_table)),
        _player(createPlayer(_game_field.start, _element_creator, game_data.player_info)),
        _hotkey_manager(FullscreenToggler(window, std::move(game_data.title), std::move(game_data.icon_src), false)),
        _key_handler(),
        _game_updater(_player->getElement().getPolygon(), window, _game_field.quadtree_el),
        _game_loop(window, _key_handler, _hotkey_manager, _game_updater){
    // Memory will be released by class Render
    auto *sprite_executor = new SpriteStateExecutor(_game_updater);
    // Memory will be released by class Render
    auto *player_executor = new PlayerExecutor(window, _key_handler, _collision_manager, _game_field.quadtree_el);
    
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
