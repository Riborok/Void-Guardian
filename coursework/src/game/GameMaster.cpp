﻿#include "../../include/game/GameMaster.hpp"

#include "../../include/game/construction/RoomCreator.hpp"
#include "../../include/game/construction/game field creation/GameFieldCreator.hpp"
#include "../../include/game/entity/player/PlayerCreator.hpp"
#include "../../include/game/executors/AnimationExecutor.hpp"
#include "../../include/game/executors/BulletExecutor.hpp"
#include "../../include/game/executors/EnemyExecutor.hpp"
#include "../../include/game/executors/RegenerationExecutor.hpp"

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
    auto& bullet_map = _entity_maps.bullet_map;
    auto& element_creator = _simple_creators.element_creator;
    auto& fighting_maps = _entity_maps.fighting_maps;
    auto*const& player = fighting_maps.player_holder.getPlayer();

    const BulletCreator bullet_creator(bullet_map, _entity_creator, quadtree_el);
    const EnemyCreator enemy_creator(_entity_creator, collision_manager, quadtree_el);
    
    // Memory will be released by class Render
    auto *animation_executor = new AnimationExecutor(quadtree_el, animation_manager);
    
    auto *player_executor = new PlayerExecutor(MouseLocator(*_window), bullet_creator, 
        collision_manager, collectible_manager, player, quadtree_el);
    
    auto *enemy_executor = new EnemyExecutor(_game_system.game_field, fighting_maps, collision_manager,
        enemy_creator, bullet_creator, lvl);

    auto *regeneration_executor = new RegenerationExecutor(fighting_maps);
    
    auto *bullet_executor = new BulletExecutor(collision_manager, bullet_map, quadtree_el,
        {_entity_maps, element_creator, animation_manager, quadtree_el, _game_state});
    
    _game_loop.registerExecutor(animation_executor);
    _game_loop.registerExecutor(player_executor);
    _game_loop.registerExecutor(enemy_executor);
    _game_loop.registerExecutor(regeneration_executor);
    _game_loop.registerExecutor(bullet_executor);
}

Player* GameMaster::createPlayer(const PlayerInventory &player_inventory, const Control& control) {
    _simple_creators.element_creator.loadTexture(ElementType::CHARACTER_DYING, player_inventory.character_num);
    const PlayerCreator player_creator(_entity_creator, _game_system.collision_manager,
        _game_system.game_field.quadtree_el);
    return player_creator.spawnPlayer({_game_system.game_field.start, 0,
        player_inventory.character_num, player_inventory.gun_num}, control, _player_offset_factor);
}

GameMaster::GameMaster(GameContext &game_context, const GameData &game_data) :
        _simple_creators(game_data.simple_sprite_infos, game_data.animated_sprite_infos),
        _entity_creator(_simple_creators.element_creator, game_data.entity_info_tables),
        _window(&game_context.window),
        _game_system(createGameSystem(game_context.player_progress.lvl, game_data)),
        _entity_maps(EntityMaps{createPlayer(game_context.player_progress.player_inventory, game_context.control)}),
        _hotkey_manager(game_context.fullscreen_toggler, _game_state),
        _game_updater(_entity_maps.fighting_maps.player_holder.getPlayer(), game_context.window, _game_system.game_field.quadtree_el),
        _game_loop(game_context.window, _hotkey_manager, _game_updater, _entity_maps.fighting_maps, game_data.health_font_src){
    createExecutors(game_context.player_progress.lvl);
}

void GameMaster::start() {
    while ((_game_state == GameState::PLAYING || !_game_system.animation_manager.isEmpty()) && _window->isOpen())
        _game_loop.nextIteration();
}

GameState GameMaster::getGameState() const { return _game_state; }

PlayerInventory GameMaster::getPlayerInventory() const {
    if (const Player* player = _entity_maps.fighting_maps.player_holder.getPlayer())
        return {player->getCharacter().getNum(),
            player->getGun().getNum()};
    return {0, 0};
}