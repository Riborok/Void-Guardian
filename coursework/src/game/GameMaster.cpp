#include "../../include/game/GameMaster.hpp"

#include "../../include/game/construction/RoomCreator.hpp"
#include "../../include/game/construction/MapCreation/GameFieldCreator.hpp"
#include "../../include/game/entity/player/PlayerCreator.hpp"
#include "../../include/game/executors/AnimationExecutor.hpp"
#include "../../include/game/executors/BulletExecutor.hpp"

GameField createGameField(const GameData &game_data, ElementCreator &element_creator, LocationCreator &location_creator) {
    const GameFieldCreator game_field_creator(game_data.latest_map_index);
    return game_field_creator.create(game_data.background_data, game_data.boundary_data,
        element_creator, location_creator);
}

void GameMaster::createExecutors() {
    // Memory will be released by class Render
    auto *animation_executor = new AnimationExecutor(_game_field.quadtree_el);
    auto *player_executor = new PlayerExecutor(
        MouseLocator(*_window), BulletCreator(_entity_maps.bullet_map, _entity_creator, _game_field.quadtree_el),
        _input_handler, _collision_manager,
        _entity_maps.player_map, _game_field.quadtree_el);
    auto *bullet_executor = new BulletExecutor(_collision_manager, _entity_maps.bullet_map,
        _game_field.quadtree_el,
        {_entity_maps, _element_creator, *animation_executor,
            _game_field.quadtree_el});
    
    _game_loop.registerExecutor(animation_executor);
    _game_loop.registerExecutor(player_executor);
    _game_loop.registerExecutor(bullet_executor);
}

void GameMaster::addPlayer() {
    const PlayerCreator player_creator(_entity_maps.player_map, _entity_creator, _game_field.quadtree_el);
    player_creator.spawnPlayer({_game_field.start, 0, 0, 0});
}

GameMaster::GameMaster(sf::RenderWindow &window, GameData &&game_data) :
        _element_creator(std::move(game_data.simple_sprite_infos), std::move(game_data.animated_sprite_infos)),
        _entity_creator(_element_creator, game_data.wraith_infos, game_data.gun_infos, game_data.bullet_infos),
        _location_creator(),

        _window(&window),
        _game_field(createGameField(game_data, _element_creator, _location_creator)),
        _entity_maps(),
        _collision_manager(std::move(game_data.collision_table)),

        _hotkey_manager(FullscreenToggler(window, std::move(game_data.title), std::move(game_data.icon_src), false)),
        _input_handler(),
        _game_updater(_entity_maps.player_map, window, _game_field.quadtree_el, _game_field.start),
        _game_loop(window, _input_handler, _hotkey_manager, _game_updater){
    createExecutors();
    addPlayer();
}

void GameMaster::start() {
    while (_window->isOpen())
        _game_loop.nextIteration();
}
