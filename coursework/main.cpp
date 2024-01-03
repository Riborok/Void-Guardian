#include "include/Launcher.hpp"
#include "include/initialization/LongCreation.hpp"

void main() {
    auto* game_setup = new GameSetup;
    auto* launcher = LongCreation::createLauncher(*game_setup);
    
    launcher->start();
    
    delete game_setup;
    delete launcher;
}