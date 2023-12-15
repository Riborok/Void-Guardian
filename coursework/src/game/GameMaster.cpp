#include "../../include/game/GameMaster.hpp"

#include "../../include/game/construction/RoomCreator.hpp"
#include "../../include/game/construction/game field creation/GameFieldCreator.hpp"
#include "../../include/game/entity/player/PlayerCreator.hpp"
#include "../../include/game/executors/AnimationExecutor.hpp"
#include "../../include/game/executors/BulletExecutor.hpp"

GameSystem GameMaster::createGameSystem(const size_t lvl, const GameData& game_data) {
    const GameFieldCreator game_field_creator(lvl);
    
    GameSystem result(game_field_creator.initialize(game_data.building_data.boundary_data),
        game_data.collision_table, _entity_creator, _game_state);
    game_field_creator.create(result.game_field, game_data.building_data, result.gun_manager,
        _simple_creators, game_data.portals_data);
    
    return result;
}

void GameMaster::createExecutors() {
    // Memory will be released by class Render
    auto *animation_executor = new AnimationExecutor(_game_system.game_field.quadtree_el);
    auto *player_executor = new PlayerExecutor(
        MouseLocator(*_window), BulletCreator(_entity_maps.bullet_map, _entity_creator,
            _game_system.game_field.quadtree_el),
        _input_handler, _game_system.collision_manager, _game_system.collectible_manager,
        _entity_maps.player_map, _game_system.game_field.quadtree_el);
    auto *bullet_executor = new BulletExecutor(_game_system.collision_manager, _entity_maps.bullet_map,
        _game_system.game_field.quadtree_el,
        {_entity_maps, _simple_creators.element_creator, *animation_executor,
            _game_system.game_field.quadtree_el, _game_state});
    
    _game_loop.registerExecutor(animation_executor);
    _game_loop.registerExecutor(player_executor);
    _game_loop.registerExecutor(bullet_executor);
}

void GameMaster::addPlayer(const PlayerInventory &player_inventory, const Control& control) {
    const PlayerCreator player_creator(_entity_maps.player_map, _entity_creator, _game_system.game_field.quadtree_el);
    player_creator.spawnPlayer({_game_system.game_field.start, 0,
        player_inventory.wraith_num, player_inventory.gun_num}, control, _player_offset_factor);
}

GameMaster::GameMaster(sf::RenderWindow &window, const PlayerProgress &player_progress, const Control& control, const GameData &game_data) :
        _simple_creators(std::move(game_data.simple_sprite_infos), std::move(game_data.animated_sprite_infos)),
        _entity_creator(_simple_creators.element_creator, game_data.wraith_infos, game_data.gun_infos, game_data.bullet_infos),
        _window(&window),
        _entity_maps(),
        _game_system(createGameSystem(player_progress.lvl, game_data)),
        _hotkey_manager(FullscreenToggler(window, game_data.window_info, false)),
        _input_handler(),
        _game_updater(_entity_maps.player_map, window, _game_system.game_field.quadtree_el, _game_system.game_field.start),
        _game_loop(window, _input_handler, _hotkey_manager, _game_updater){
    createExecutors();
    addPlayer(player_progress.player_inventory, control);
}

void GameMaster::start() {
    while (_game_state == GameState::PLAYING && _window->isOpen())
        _game_loop.nextIteration();
}

GameState GameMaster::getGameState() const { return _game_state; }

PlayerInventory GameMaster::getPlayerInventory() const {
    if (_entity_maps.player_map.getMap().empty())
        return {0, 0};

    const auto* player = _entity_maps.player_map.getMap().begin()->second;
    return {player->getWraith().getNum(), player->getGun().getNum()};
}
