#include "../../include/game/GameManager.hpp"

#include "../../include/game/GameData.hpp"
#include "../../include/game/GameMaster.hpp"

void GameManager::setLvlTitle() const {
    _game_context->window.setTitle("Current lvl: " + std::to_string(_game_context->player_progress.lvl));
}

GameManager::GameManager(GameContext& game_context, GameData &&game_data, const std::string& src):
        _game_context(&game_context), _game_data(std::move(game_data)){
    if (sf::Image image; image.loadFromFile(src)) {
        image.createMaskFromColor(sf::Color::Transparent);
        _cursor.loadFromPixels(image.getPixelsPtr(), image.getSize(), {0, 0});
    }
    else
        _cursor.loadFromSystem(sf::Cursor::Arrow);
}

GameState GameManager::startGame() const {
    _game_context->window.setMouseCursor(_cursor);
    
    GameState game_state;
    do {
        setLvlTitle();
        auto *game_master = new GameMaster(*_game_context, _game_data);
        game_master->start();
        
        if (game_state = game_master->getGameState(); game_state == GameState::NEXT_LEVEL) {
            auto& player_progress = _game_context->player_progress;
            ++player_progress.lvl;
            player_progress.player_inventory = game_master->getPlayerInventory();
        }
        
        delete game_master;
    } while (game_state == GameState::NEXT_LEVEL);
    return game_state;
}
