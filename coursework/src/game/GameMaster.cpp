#include "../../include/game/GameMaster.hpp"

#include "../../include/game/construction/RoomCreator.hpp"
#include "../../include/game/construction/game field creation/GameFieldCreator.hpp"
#include "../../include/game/entity/player/PlayerCreator.hpp"
#include "../../include/game/executors/AnimationExecutor.hpp"
#include "../../include/game/executors/BulletExecutor.hpp"
#include "../../include/game/executors/EnemyExecutor.hpp"

GameSystem GameMaster::createGameSystem(const size_t lvl, const GameData& game_data) {
    const GameFieldCreator game_field_creator(lvl);

    const BuildingInfo building_info(game_data.building_data, lvl);
    GameSystem result(game_field_creator.initialize(building_info.boundary_info),
        game_data.collision_table, _entity_creator, _game_state);
    game_field_creator.create(result.game_field, building_info, result.gun_manager,
        _simple_creators, game_data.portals_data);
    
    return result;
}

void GameMaster::createExecutors(const size_t lvl) {
    auto& quadtree_el = _game_system.game_field.quadtree_el;
    auto& collectible_manager = _game_system.collectible_manager;
    auto& collision_manager = _game_system.collision_manager;
    auto& animation_manager = _game_system.animation_manager;
    auto& bullet_map = _entity_maps.getBulletMap();
    auto& element_creator = _simple_creators.element_creator;
    auto& enemy_map = _entity_maps.getEnemyMap();
    auto& player = _entity_maps.getPlayer();
    
    // Memory will be released by class Render
    auto *animation_executor = new AnimationExecutor(quadtree_el, animation_manager);
    
    auto *player_executor = new PlayerExecutor(MouseLocator(*_window),
        BulletCreator(bullet_map, _entity_creator, quadtree_el), _input_handler,
        collision_manager, collectible_manager, player, quadtree_el);
    
    auto* enemy_executor = new EnemyExecutor(_game_system.game_field, enemy_map, player, collision_manager,
        {_entity_creator, collision_manager, quadtree_el}, lvl);
    
    auto *bullet_executor = new BulletExecutor(collision_manager, bullet_map, quadtree_el,
        {_entity_maps, element_creator, animation_manager, quadtree_el, _game_state});
    
    _game_loop.registerExecutor(animation_executor);
    _game_loop.registerExecutor(player_executor);
    _game_loop.registerExecutor(enemy_executor);
    _game_loop.registerExecutor(bullet_executor);
}

Player* GameMaster::createPlayer(const PlayerInventory &player_inventory, const Control& control) {
    _simple_creators.element_creator.loadTexture(ElementType::CHARACTER_DYING, player_inventory.character_num);
    const PlayerCreator player_creator(_entity_creator, _game_system.collision_manager,
        _game_system.game_field.quadtree_el);
    return player_creator.spawnPlayer({_game_system.game_field.start, 0,
        player_inventory.character_num, player_inventory.gun_num}, control, _player_offset_factor);
}

GameMaster::GameMaster(sf::RenderWindow &window, FullscreenToggler &fullscreen_toggler,
        const PlayerProgress &player_progress, const Control& control, const GameData &game_data) :
        _simple_creators(game_data.simple_sprite_infos, game_data.animated_sprite_infos),
        _entity_creator(_simple_creators.element_creator, game_data.entity_info_tables),
        _window(&window),
        _game_system(createGameSystem(player_progress.lvl, game_data)),
        _entity_maps(EntityMaps{createPlayer(player_progress.player_inventory, control)}),
        _hotkey_manager(fullscreen_toggler),
        _input_handler(),
        _game_updater(_entity_maps.getPlayer(), window, _game_system.game_field.quadtree_el),
        _game_loop(window, _input_handler, _hotkey_manager, _game_updater){
    createExecutors(player_progress.lvl);
}

void GameMaster::start() {
    while ((_game_state == GameState::PLAYING || !_game_system.animation_manager.isEmpty()) && _window->isOpen())
        _game_loop.nextIteration();
}

GameState GameMaster::getGameState() const { return _game_state; }

PlayerInventory GameMaster::getPlayerInventory() const {
    if (_entity_maps.getPlayer())
        return {_entity_maps.getPlayer()->getCharacter().getNum(),
            _entity_maps.getPlayer()->getGun().getNum()};
    return {0, 0};
}