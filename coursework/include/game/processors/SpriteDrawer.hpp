#pragma once
#include <queue>
#include <SFML/Graphics/RenderWindow.hpp>

#include "../../additionally/other types/ElementCollisionSet.hpp"
#include "../../element/Element.hpp"

class SpriteDrawer final {
    static constexpr sf::Uint8 DEFAULT_COLOR_VALUE = 36;
    typedef const Element* Value;
    typedef std::priority_queue<Value, std::vector<Value>, ElementCompare> SpritesPQ;

    sf::Sprite _sprite;
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