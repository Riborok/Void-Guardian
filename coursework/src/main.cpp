#include <SFML/Graphics.hpp>
#include <ctime>

#include "model/entity/RectangularEntity.h"
#include "model/Quadtree/Quadtree.h"

int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Void Guardian");
    
    sf::Image icon;
    if (icon.loadFromFile("./img/icon.png")) { window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr()); }

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
        quadtree.Insert(rect);

    std::unordered_set<RectangularEntity*, IdentifiableHash> collision;
    quadtree.GetCollisions(rects[rects.size() - 1], collision);
    
    for (auto &rect : rects)
        quadtree.Remove(rect);
    
        
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.display();
    }

    return 0;
}