#include "../../include/game/GameMaster.hpp"

#include "../../include/game/construction/RoomCreator.hpp"
#include "../../include/game/construction/MapCreation/GameFieldCreator.hpp"
#include "../../include/game/executors/SpriteStateExecutor.hpp"

GameField createGameField(const GameData &game_data, ElementCreator &element_creator, LocationCreator &location_creator) {
    const GameFieldCreator game_field_creator(game_data.latest_map_index);
    return game_field_creator.create(game_data.background_data, game_data.boundary_data,
        element_creator, location_creator);
}

GameMaster::GameMaster(sf::RenderWindow &window, GameData &&game_data) :
        _element_creator(std::move(game_data.simple_sprite_infos), std::move(game_data.animated_sprite_infos)),
        _entity_creator(_element_creator, game_data.wraith_infos, game_data.gun_infos, game_data.bullet_infos),
        _window(&window),
        _game_field(createGameField(game_data, _element_creator, _location_creator)),
        _collision_manager(std::move(game_data.collision_table)),
        _player(_entity_creator.createPlayer(_game_field.start, 0, 0, 0)),
        _hotkey_manager(FullscreenToggler(window, std::move(game_data.title), std::move(game_data.icon_src), false)),
        _game_updater(_player->getWraith().getElement().getPolygon(), window, _game_field.quadtree_el),
        _game_loop(window, _key_handler, _hotkey_manager, _game_updater){
    // Memory will be released by class Render
    auto *sprite_executor = new SpriteStateExecutor(_game_updater);
    // Memory will be released by class Render
    auto *player_executor = new PlayerExecutor(window, _key_handler, _collision_manager, _game_field.quadtree_el);
    
    _game_loop.registerExecutor(sprite_executor);
    _game_loop.registerExecutor(player_executor);
    
    player_executor->addPlayer(_player);
    _game_field.quadtree_el.insert(&_player->getWraith().getElement());
    _game_field.quadtree_el.insert(&_player->getGun().getElement());
}

void GameMaster::start() {
    while (_window->isOpen()) {
        _game_loop.nextIteration();
    }
}
