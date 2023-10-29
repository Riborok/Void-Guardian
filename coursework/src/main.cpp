// ReSharper disable CppIncompleteSwitchStatement CppDefaultCaseNotHandledInSwitchStatement CppClangTidyClangDiagnosticSwitch
#include <SFML/Graphics.hpp>
#include <ctime>

#include "element/ElementCreation.h"
#include "game/GameMaster.h"

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Void Guardian");
    
    sf::Image icon;
    if (icon.loadFromFile("./img/icon.png")) { window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr()); }

    auto element = ElementCreation::create(sf::Vector2f(0, 0), 0, Types::ElementType::WRAITH, 0, 0.3f);
    
    GameMaster game_master(window);
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
                element->setSpritePosition(1);
                game_master.keyHandler().handleKeyUp(event.key.code);
                break;
            case sf::Event::KeyReleased:
                element->setSpritePosition(0);
                game_master.keyHandler().handleKeyDown(event.key.code);
                break;
            }
        }

        int delta_time = clock.restart().asMilliseconds();
        auto &sprite = element->getSprite();
        
        auto *animated_sprite = dynamic_cast<AnimatedSprite*>(&sprite);
        if (animated_sprite)
            animated_sprite->changeState(delta_time);
        
        window.clear();
        window.draw(sprite);
        window.display();
    }
    
    delete element;
    return 0;
}
