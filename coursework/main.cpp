#include "include/game/GameData.hpp"
#include "include/game/GameMaster.hpp"
#include "include/initialization/GameDataInitialization.hpp"

void main() {
    auto *window = new sf::RenderWindow();

    const auto* game_data = new GameData(GameDataInitialization::initialize());
    auto *game_master = new GameMaster(*window, {{2, 0}, 0}, *game_data);
    
    game_master->start();

    delete game_data;
    delete window;
    delete game_master;
}