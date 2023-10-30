// ReSharper disable CppIncompleteSwitchStatement CppDefaultCaseNotHandledInSwitchStatement CppClangTidyClangDiagnosticSwitch
#include <SFML/Graphics.hpp>
#include <ctime>

#include "element/ElementCreation.h"
#include "game/GameMaster.h"
#include "game/construction/CreatingRectangularLocation.h"
#include "Quadtree/Quadtree.h"

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Void Guardian", sf::Style::Default);
    
    sf::Image icon;
    if (icon.loadFromFile("./img/Icon.png")) { window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr()); }

    GameMaster game_master(window);
    Quadtree quadtree(0, 0, static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y));
    CreatingRectangularLocation::createBackground(0, {0, 0}, {1920, 1024}, quadtree, 1.0f);
    auto *wraith = ElementCreation::create({0, 0}, 0, Types::WRAITH, 0, 1);
    quadtree.remove(wraith);
    sf::Clock clock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::LostFocus:
                game_master.keyHandler().clearKeys();
                break;
            case sf::Event::GainedFocus:
                break;
            case sf::Event::KeyPressed:
                game_master.keyHandler().handleKeyUp(event.key.code);
                break;
            case sf::Event::KeyReleased:
                game_master.keyHandler().handleKeyDown(event.key.code);
                break;
            }
        }

        std::unordered_set<Element*, IdentifiableHash> collisions;
        RectangularCoverage rect(0, 0, static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y));
        quadtree.getCollisions(rect, collisions);
        
        game_master.spriteDrawer().add(collisions);
        game_master.spriteDrawer().drawAll(clock.restart().asMilliseconds());
    }
    
    return 0;
}
