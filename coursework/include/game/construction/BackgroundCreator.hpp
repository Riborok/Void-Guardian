﻿#pragma once
#include "../../additionally/QuadtreeEl.hpp"
#include "../../additionally/TypesDef.hpp"

class BackgroundCreator final {
    int _num;
    sf::Vector2f _scale;
    sf::Vector2i _delta;
    QuadtreeEl *_quadtree;
public:
    BackgroundCreator(const int num, const sf::Vector2f &scale, QuadtreeEl &quadtree);

    /**
     * Creates a background grid of elements in a specified region.
     * @param p0 The starting point of the grid.
     * @param p1 The ending point of the grid.
     */
    void createBackground(const sf::Vector2i &p0, const sf::Vector2i &p1) const;
    
    /**
     * Creates a background grid of elements using a starting point and the number of elements along the X and Y axes.
     * @param p0 The starting point of the grid.
     * @param count_x The amount of elements along the X-axis.
     * @param count_y The amount of elements along the Y-axis.
     */
    void createBackground(const sf::Vector2i &p0, const int count_x, const int count_y) const;
    
    ~BackgroundCreator() noexcept = default;
    BackgroundCreator(BackgroundCreator&&) noexcept = delete;
    BackgroundCreator& operator=(BackgroundCreator&&) noexcept = delete;
    BackgroundCreator(const BackgroundCreator&) noexcept = delete;
    BackgroundCreator& operator=(const BackgroundCreator&) noexcept = delete;
};
