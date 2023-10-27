// ReSharper disable CppIncompleteSwitchStatement CppDefaultCaseNotHandledInSwitchStatement CppClangTidyClangDiagnosticSwitch
#include <SFML/Graphics.hpp>
#include <ctime>

#include "game/GameMaster.h"
#include "model/entity/RectangularEntity.h"
#include "Quadtree/Quadtree.h"
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

    //
    std::vector<RectangularEntity> rects;
    rects.emplace_back(sf::Vector2f{0, 0}, 5, 5, 0, 0);
    rects.emplace_back(sf::Vector2f{5, 5}, 5, 5, 0, 1);
    rects.emplace_back(sf::Vector2f{10, 10}, 5, 5, 0, 2);
    rects.emplace_back(sf::Vector2f{15, 15}, 5, 5, 0, 3);
    rects.emplace_back(sf::Vector2f{20, 20}, 5, 5, 0, 4);
    rects.emplace_back(sf::Vector2f{25, 25}, 5, 5, 0, 5);
    rects.emplace_back(sf::Vector2f{30, 30}, 5, 5, 0, 6);
    rects.emplace_back(sf::Vector2f{35, 35}, 5, 5, 0, 7);
    rects.emplace_back(sf::Vector2f{40, 40}, 5, 5, 0, 8);
    rects.emplace_back(sf::Vector2f{0, 0}, 1280, 720, 0, 9);
    
    Quadtree<RectangularEntity> quadtree(0, 0,
                                         static_cast<float>(window.getSize().x),
                                         static_cast<float>(window.getSize().y));
    
    for (auto &rect : rects)
        quadtree.insert(rect);

    std::unordered_set<RectangularEntity*, IdentifiableHash> collision;
    quadtree.getCollisions(rects[rects.size() - 1], collision);
    
    for (auto &rect : rects)
        quadtree.remove(rect);
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
                game_master.keyHandler().ClearKeys();
                break;
            case sf::Event::GainedFocus:
                break;
            case sf::Event::KeyPressed:
                game_master.keyHandler().HandleKeyUp(event.key.code);
                break;
            case sf::Event::KeyReleased:
                game_master.keyHandler().HandleKeyDown(event.key.code);
                break;
            }
        }

        int delta_time = clock.restart().asMilliseconds();

        animated_sprite.changeState(delta_time);

        angle += 0.1f;
        sprite.setRotation(angle);
        window.clear();
        window.draw(animated_sprite);
        window.draw(sprite);
        window.display();
    }
    return 0;
}
