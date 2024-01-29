#pragma once
#include "../../geometry/collision/ElementCollisionSet.hpp"
#include "../entity/EntityMaps.hpp"

struct BarColor final {
    sf::Color main_color;
    sf::Color full_color;
    BarColor(const sf::Color main_color, const sf::Color full_color):
        main_color(main_color), full_color(full_color){}
};

struct BarsColors final {
    sf::Color text;
    BarColor health;
    BarColor armor;
    BarsColors(const sf::Color text, const BarColor &health, const BarColor &armor):
        text(text), health(health), armor(armor){}
};

class FightingInfoDrawer final {
    static constexpr int FONT_SIZE = 10;
    static constexpr float OFFSET_FROM_P0 = 8;
    static constexpr float OFFSET_FROM_BAR = 12;
    static constexpr float BARS_HEIGHT = 10;
    static constexpr std::streamsize PRECISION_FACTOR = 3;
    
    sf::RenderWindow *_window;
    sf::Font _health_font;
    BarsColors _bars_colors;
    FightingMaps *_fighting_maps;
    [[nodiscard]] FightingEntity& getFightingEntity(const size_t id) const;
    void drawText(const sf::Vector2f& position, const sf::Vector2f& size, sf::Text &text) const;
    void drawRect(const sf::Vector2f &size, const sf::Color& color, sf::RectangleShape &rectangle) const;
    void drawRects(const sf::Vector2f& position, sf::Vector2f size, const float width_factor,
        const BarColor &bar_color, sf::RectangleShape &rectangle) const;
    void drawBar(const sf::Vector2f& position, const float width, const float width_factor,
        const BarColor &bar_color, sf::RectangleShape &rectangle, sf::Text &text) const;
    
    static void setText(sf::Text &text, const std::string &str);
public:
    FightingInfoDrawer(sf::RenderWindow &window, FightingMaps &fighting_maps, const std::string &health_font_src,
        const BarsColors &bars_colors = {sf::Color::Black,
            {{13, 236, 35}, {9, 174, 25}},
        {{9, 170, 233}, {13, 118, 158}}});
    void drawHealthBars(const ElementCollisionSet &elements) const;
    
    ~FightingInfoDrawer() noexcept = default;
    FightingInfoDrawer(const FightingInfoDrawer&) noexcept = delete;
    FightingInfoDrawer& operator=(const FightingInfoDrawer&) noexcept = delete;
    FightingInfoDrawer(FightingInfoDrawer&&) noexcept = default;
    FightingInfoDrawer& operator=(FightingInfoDrawer&&) noexcept = delete;
};
