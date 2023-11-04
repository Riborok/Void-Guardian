#include <ctime>

#include "game/GameMaster.h"

void main() {
    srand(static_cast<unsigned>(time(nullptr)));
    
    sf::RenderWindow window;
    
    GameMaster game_master(window);
    game_master.start();
}
