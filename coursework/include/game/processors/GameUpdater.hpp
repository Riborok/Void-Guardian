#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

#include "../WindowParam.hpp"
#include "../../geometry/collision/ElementCollisionSet.hpp"
#include "../../quadtree/quadtree type defs/QuadtreeEl.hpp"
#include "../entity/player/PlayerMap.hpp"

class GameUpdater final {
    PlayerMap *_player_map;
    sf::RenderWindow *_window;
    QuadtreeEl *_quadtree;
    sf::Vector2f _prev_focus;
    WindowParam _window_param;

    [[nodiscard]] const sf::Vector2f& getFocus();
public:
    GameUpdater(PlayerMap &player_map, sf::RenderWindow &window, QuadtreeEl &quadtree);
    
    void updateView();
    void fillCollisionSet(ElementCollisionSet &element_collision_set);
    WindowParam &getWindowParam();
    
    ~GameUpdater() noexcept = default;
    
    GameUpdater(const GameUpdater&) noexcept = delete;
    GameUpdater& operator=(const GameUpdater&) noexcept = delete;
    GameUpdater(GameUpdater&&) noexcept = delete;
    GameUpdater& operator=(GameUpdater&&) noexcept = delete;
};
