#pragma once
#include "../Launcher.hpp"

namespace LongCreation {
    Launcher *createLauncher(GameSetup &game_setup);
    GameMaster *createGameMaster(GameSetup& game_setup, const GameData &game_data);
    void freeGameMaster(GameSetup& game_setup, GameMaster *game_master);
}