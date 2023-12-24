#include "../../../include/game/processors/FightingInfoDrawer.hpp"
#include "../../../include/game/identifiable/ElementIdTracker.hpp"
#include "../../../include/geometry/GeomAuxiliaryFunc.hpp"

FightingEntity& FightingInfoDrawer::getFightingEntity(const size_t id) const {
    const auto& enemy_map = _fighting_maps->enemy_map.getMap();
    if (const auto it_enemy = enemy_map.find(id); it_enemy != enemy_map.end())
        return *it_enemy->second;
    
    if (const auto& player = _fighting_maps->player_holder.getPlayer(); player->getId() == id)
        return *player;

    throw std::out_of_range("FightingEntity with specified ID not found");
}

FightingInfoDrawer::FightingInfoDrawer(sf::RenderWindow &window, FightingMaps& fighting_maps,
                                       const std::string &font_src, const BarsColors &bars_colors):
    _window(&window), _bars_colors(bars_colors), _fighting_maps(&fighting_maps) { _font.loadFromFile(font_src); }

void FightingInfoDrawer::drawHealthBars(const ElementCollisionSet &elements) const {
    sf::Text label_text("", _font, 10); 
    label_text.setFillColor(_bars_colors.text);

    sf::RectangleShape rectangle;
    
    for (const auto& element : elements)
        if (const size_t id(element->getId()); ElementIdTracker::extractType(id) == ElementType::CHARACTER) {
            const auto& fighting_entity = getFightingEntity(id);
            
            const auto& polygon = element->getPolygon();
            sf::Vector2f p0(polygon.getPoints()[0]);
            const auto width = polygon.getBoundingRectWidth();

            p0.y -= OFFSET_FROM_P0;
            if (fighting_entity.getArmorStrengthRatio() > 0) {
                setText(label_text, GeomAuxiliaryFunc::roundNum(fighting_entity.getArmorStrengthRatio(), PRECISION_FACTOR));
                drawBar(p0, width, fighting_entity.calcArmorStrengthRatio(), _bars_colors.armor, rectangle, label_text);
                p0.y -= OFFSET_FROM_BAR;
            }
            
            setText(label_text, std::to_string(fighting_entity.getHealth()));
            drawBar(p0, width, fighting_entity.calcHealthRatio(), _bars_colors.health, rectangle, label_text);
        }
}

void FightingInfoDrawer::drawText(const sf::Vector2f& position, const sf::Vector2f& size, sf::Text& text) const {
    text.setPosition(position.x + size.x / 2.0f, position.y + size.y / 2.0f);
    _window->draw(text);
}

void FightingInfoDrawer::drawRect(const sf::Vector2f& position, sf::Vector2f& size, const float width_factor,
        const BarColor &bar_color, sf::RectangleShape &rectangle) const {
    rectangle.setPosition(position);
    rectangle.setSize(size);
    rectangle.setFillColor(bar_color.full_color);
    _window->draw(rectangle);

    size.x *= width_factor;
    rectangle.setSize(size);
    rectangle.setFillColor(bar_color.main_color);
    _window->draw(rectangle);
}

void FightingInfoDrawer::drawBar(const sf::Vector2f& position, const float width, const float width_factor,
                                 const BarColor &bar_color, sf::RectangleShape &rectangle, sf::Text &text) const {
    sf::Vector2f size{width, BARS_HEIGHT};
    drawRect(position, size, width_factor, bar_color, rectangle);
    drawText(position, size, text);
}

void FightingInfoDrawer::setText(sf::Text& text, const std::string& str) {
    text.setString(str);
    const auto text_bounds = text.getLocalBounds();
    text.setOrigin(text_bounds.left + text_bounds.width / 2.0f, text_bounds.top + text_bounds.height / 2.0f);
}