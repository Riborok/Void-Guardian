#include "../../../include/game/construction/BackgroundCreator.hpp"

BackgroundCreator::BackgroundCreator(const BackgroundInfo &building_info, QuadtreeEl &quadtree, ElementCreator &element_creator) :
    _building_info(building_info), _quadtree(&quadtree), _element_creator(&element_creator){}

void BackgroundCreator::createBackground(const sf::Vector2i &p0, const sf::Vector2i &p1) const {
    int y = p0.y;
    while (y < p1.y) {
        int x = p0.x;
        while (x < p1.x) {
            _quadtree->insert(_element_creator->create({
                {static_cast<float>(x), static_cast<float>(y)}, 0, ElementType::BACKGROUND,
                _building_info.num, _building_info.background_parameters.scale}));
            x += _building_info.background_parameters.delta.x;
        }
        y += _building_info.background_parameters.delta.y;
    }
}

void BackgroundCreator::createBackground(const sf::Vector2i &p0, const int count_x, const int count_y) const {
    const sf::Vector2i p1(p0.x + _building_info.background_parameters.delta.x * count_x,
        p0.y + _building_info.background_parameters.delta.y * count_y);
    createBackground(p0, p1);
}