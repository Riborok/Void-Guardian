#pragma once
#include <queue>
#include <SFML/Graphics/RenderWindow.hpp>

#include "../../additionally/TypesDef.hpp"
#include "../../element/Element.hpp"

class SpriteDrawer final {
    static constexpr sf::Uint8 DEFAULT_COLOR_VALUE = 36;
    typedef std::priority_queue<const SimpleSprite*, std::vector<const SimpleSprite*>, SimpleSpriteCompare> SpritesPQ;

    SpritesPQ _pq;
    sf::RenderWindow *_window;
    const ElementCollisionSet *_elements;
    sf::Color _color;

    void addToPq();
    void drawFromPq();

public:
    SpriteDrawer(sf::RenderWindow &window, const ElementCollisionSet &elements,
        const sf::Color &color = {DEFAULT_COLOR_VALUE, DEFAULT_COLOR_VALUE, DEFAULT_COLOR_VALUE});

    void drawAll();

    ~SpriteDrawer() noexcept = default;

    SpriteDrawer(const SpriteDrawer&) noexcept = delete;
    SpriteDrawer& operator=(const SpriteDrawer&) noexcept = delete;
    SpriteDrawer(SpriteDrawer&&) noexcept = delete;
    SpriteDrawer& operator=(SpriteDrawer&&) noexcept = delete;
};