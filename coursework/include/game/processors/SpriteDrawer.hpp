#pragma once
#include <queue>
#include <SFML/Graphics/RenderWindow.hpp>

#include "../../element/Element.hpp"
#include "../../geometry/collision/ElementCollisionSet.hpp"

class SpriteDrawer final {
    static constexpr sf::Uint8 DEFAULT_COLOR_VALUE = 36;
    typedef const Element* Value;
    typedef std::priority_queue<Value, std::vector<Value>, ElementCompare> SpritesPQ;
    
    sf::RenderWindow *_window;
    sf::Color _color;

    void drawFromPq(SpritesPQ &pq) const;
public:
    explicit SpriteDrawer(sf::RenderWindow &window, const sf::Color &color =
        {DEFAULT_COLOR_VALUE, DEFAULT_COLOR_VALUE, DEFAULT_COLOR_VALUE});

    void drawAll(const ElementCollisionSet &elements) const;

    ~SpriteDrawer() noexcept = default;

    SpriteDrawer(const SpriteDrawer&) noexcept = delete;
    SpriteDrawer& operator=(const SpriteDrawer&) noexcept = delete;
    SpriteDrawer(SpriteDrawer&&) noexcept = delete;
    SpriteDrawer& operator=(SpriteDrawer&&) noexcept = delete;
};
