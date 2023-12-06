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
    sf::Vector2f _default_focus;
    WindowParam _window_param;

    [[nodiscard]] sf::Vector2f getFocus() const;
public:
    GameUpdater(PlayerMap &player_map, sf::RenderWindow &window, QuadtreeEl &quadtree,
        const sf::Vector2f &default_focus);
    
    void updateView();
    void fillCollisionSet(ElementCollisionSet &element_collision_set) const;
    WindowParam &getWindowParam();
    
    ~GameUpdater() noexcept = default;
    
    GameUpdater(const GameUpdater&) noexcept = delete;
    GameUpdater& operator=(const GameUpdater&) noexcept = delete;
    GameUpdater(GameUpdater&&) noexcept = delete;
    GameUpdater& operator=(GameUpdater&&) noexcept = delete;
};
