#pragma once
#include <queue>
#include <unordered_set>
#include <SFML/Graphics/RenderWindow.hpp>

#include "../../element/Element.hpp"

class SpriteDrawer final {
    static constexpr sf::Uint8 DEFAULT_COLOR_VALUE = 36;

    std::priority_queue<SimpleSprite*, std::vector<SimpleSprite*>, SimpleSpriteCompare> _pq;
    sf::RenderWindow *_window;
    std::unordered_set<Element*, IdentifiableHash> *_elements;
    sf::Color _color;

    void addToPq();
    void drawFromPq();

public:
    SpriteDrawer(sf::RenderWindow &window, std::unordered_set<Element*, IdentifiableHash> &elements,
        const sf::Color &color = {DEFAULT_COLOR_VALUE, DEFAULT_COLOR_VALUE, DEFAULT_COLOR_VALUE});

    void drawAll();

    ~SpriteDrawer() noexcept = default;

    SpriteDrawer(const SpriteDrawer&) noexcept = delete;
    SpriteDrawer& operator=(const SpriteDrawer&) noexcept = delete;
    SpriteDrawer(SpriteDrawer&&) noexcept = delete;
    SpriteDrawer& operator=(SpriteDrawer&&) noexcept = delete;
};