#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

#include "../WindowParam.hpp"
#include "../../geometry/collision/ElementCollisionSet.hpp"
#include "../../model/polygon/Polygon.hpp"
#include "../../quadtree/quadtree type defs/QuadtreeEl.hpp"

class GameUpdater final {
    const Polygon *_focus;
    sf::RenderWindow *_window;
    QuadtreeEl *_quadtree;
    WindowParam _window_param;
public:
    GameUpdater(const Polygon &focus, sf::RenderWindow &window, QuadtreeEl &quadtree);
    
    void updateView();
    void fillCollisionSet(ElementCollisionSet &element_collision_set) const;
    WindowParam &getWindowParam();
    
    ~GameUpdater() noexcept = default;
    
    GameUpdater(const GameUpdater&) noexcept = delete;
    GameUpdater& operator=(const GameUpdater&) noexcept = delete;
    GameUpdater(GameUpdater&&) noexcept = delete;
    GameUpdater& operator=(GameUpdater&&) noexcept = delete;
};
