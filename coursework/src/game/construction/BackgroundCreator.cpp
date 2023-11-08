#include "../../../include/game/construction/BackgroundCreator.hpp"

#include "../../../include/additionally/AdditionalFunc.hpp"
#include "../../../include/additionally/Constants.hpp"
#include "../../../include/additionally/TypesDef.hpp"
#include "../../../include/element/ElementCreation.hpp"

BackgroundCreator::BackgroundCreator(const int num, const sf::Vector2f &scale, QuadtreeEl &quadtree) :
    _num(num), _scale(scale), _delta(AdditionalFunc::getScaledSize(Constants::BACKGROUND_SIZE, scale)),
    _quadtree(&quadtree){}

void BackgroundCreator::createBackground(const sf::Vector2i &p0, const sf::Vector2i &p1) const {
    int y = p0.y;
    while (y < p1.y) {
        int x = p0.x;
        while (x < p1.x) {
            _quadtree->insert(ElementCreation::create({static_cast<float>(x), static_cast<float>(y)},
                0, ElementTypes::BACKGROUND, _num, _scale));
            x += _delta.x;
        }
        y += _delta.y;
    }
}

void BackgroundCreator::createBackground(const sf::Vector2i &p0, const int count_x, const int count_y) const {
    const sf::Vector2i p1(p0.x + _delta.x * count_x,p0.y + _delta.y * count_y);
    createBackground(p0, p1);
}