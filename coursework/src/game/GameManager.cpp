#include "../../include/game/GameManager.hpp"

#include "../../include/game/GameData.hpp"
#include "../../include/game/GameMaster.hpp"
#include "../../include/initialization/LongCreation.hpp"

AnimatedSprites GameManager::createAnimatedSprites(const CharacterLimits &character_limits) {
    AnimatedSprites result;
    result.reserve(character_limits.last_index - character_limits.start_index + 1);
    for (size_t i = character_limits.start_index; i <= character_limits.last_index; ++i)
        result.emplace_back(_game_data.animated_sprite_infos.getInfo(ElementType::CHARACTER, i)[0]);
    return result;
}

void GameManager::setLvlTitle() const {
    auto& game_context = _game_setup->game_context;
    game_context.window.setTitle("Current lvl: " + std::to_string(game_context.player_progress.lvl));
}

GameManager::GameManager(GameSetup& game_setup, PauseManager &pause_manager, GameData &&game_data,
        const std::string& src, const Colors &choose_colors, const CharacterLimits &character_limits):
        _game_setup(&game_setup), _pause_subset(pause_manager), _game_data(std::move(game_data)),
        _choose_character_manager(game_setup.game_context, createAnimatedSprites(character_limits),
            _game_data.entity_info_tables.character_infos, *game_setup.gui_manager.font,
            *game_setup.gui_manager.cursors, choose_colors){
    if (sf::Image image; image.loadFromFile(src)) {
        image.createMaskFromColor(sf::Color::Transparent);
        _pause_subset.cursor.loadFromPixels(image.getPixelsPtr(), image.getSize(), {0, 0});
    }
    else
        _pause_subset.cursor.loadFromSystem(sf::Cursor::Arrow);
}

GameState GameManager::startGame() {
    auto game_state = GameState::NEXT_LEVEL;
    _choose_character_manager.start(game_state);
    while (game_state == GameState::NEXT_LEVEL) {
        setLvlTitle();
        auto *game_master = LongCreation::createGameMaster(*_game_setup, _pause_subset, _game_data);

        _game_setup->game_context.window.setMouseCursor(_pause_subset.cursor);
        game_master->start();
        if (game_state = game_master->getGameState(); game_state == GameState::NEXT_LEVEL) {
            auto& player_progress = _game_setup->game_context.player_progress;
            ++player_progress.lvl;
            player_progress.player_inventory = game_master->getPlayerInventory();
        }
        
        LongCreation::freeGameMaster(*_game_setup, game_master);
    } 
    return game_state;
}