// ReSharper disable CppIncompleteSwitchStatement CppDefaultCaseNotHandledInSwitchStatement CppClangTidyClangDiagnosticSwitch
#include <SFML/Graphics.hpp>
#include <ctime>

#include "game/GameMaster.h"

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Void Guardian");
    
    sf::Image icon;
    if (icon.loadFromFile("./img/icon.png")) { window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr()); }

    GameMaster game_master(window);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::LostFocus:
                game_master.KeyHandler().ClearKeys();
                break;
            case sf::Event::GainedFocus:
                break;
            case sf::Event::KeyPressed:
                game_master.KeyHandler().HandleKeyUp(event.key.code);
                break;
            case sf::Event::KeyReleased:
                game_master.KeyHandler().HandleKeyDown(event.key.code);
                break;
            }
        }

        window.clear();
        window.display();
    }
    return 0;
}