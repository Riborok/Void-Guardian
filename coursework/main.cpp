#include "include/game/GameMaster.hpp"

void main() {
    sf::RenderWindow window;
    
    GameMaster game_master(window);
    game_master.start();
}
