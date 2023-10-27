// ReSharper disable CppIncompleteSwitchStatement CppDefaultCaseNotHandledInSwitchStatement CppClangTidyClangDiagnosticSwitch
#include <SFML/Graphics.hpp>
#include <ctime>

#include "game/GameMaster.h"
#include "sprite/AnimatedSprite.h"
#include "sprite/SimpleSprite.h"

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Void Guardian");
    
    sf::Image icon;
    if (icon.loadFromFile("./img/icon.png")) { window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr()); }

    //
    AnimatedSprite animated_sprite(WRAITH, 0, 12, 35, 0);
    animated_sprite.setPosition(50, 50);
    animated_sprite.setScale(0.25f, 0.25f);
    
    SimpleSprite sprite(GUN, 0, 0);
    //sf::Texture texture;
    //texture.loadFromFile("./img/Guns/Gun_0.png");
    //sf::Sprite sprite(texture);
    sprite.setPosition(75, 100);
    sprite.setScale(-1, 1);
    float angle = 0.0f;
    //

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

        int delta_time = clock.restart().asMilliseconds();

        animated_sprite.ChangeState(delta_time);

        angle += 0.1f;
        sprite.setRotation(angle);
        window.clear();
        window.draw(animated_sprite);
        window.draw(sprite);
        window.display();
    }
    return 0;
}
