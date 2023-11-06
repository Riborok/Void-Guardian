#include "game/GameMaster.h"

void main() {
    sf::RenderWindow window;
    
    GameMaster game_master(window);
    game_master.start();
}
