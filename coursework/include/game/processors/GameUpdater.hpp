#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

#include "../WindowParam.hpp"
#include "../../geometry/collision/ElementCollisionSet.hpp"
#include "../../quadtree/quadtree type defs/QuadtreeEl.hpp"
#include "../entity/player/Player.hpp"

class GameUpdater final {
    Player *const* _player;
    sf::RenderWindow *_window;
    QuadtreeEl *_quadtree;
    sf::Vector2f _prev_focus;
    WindowParam _window_param;

    [[nodiscard]] const sf::Vector2f& getFocus();
public:
    GameUpdater(Player *const& player, sf::RenderWindow &window, QuadtreeEl &quadtree);
    
    void updateView();
    void fillCollisionSet(ElementCollisionSet &element_collision_set);
    WindowParam &getWindowParam();
    
    ~GameUpdater() noexcept = default;
    
    GameUpdater(const GameUpdater&) noexcept = delete;
    GameUpdater& operator=(const GameUpdater&) noexcept = delete;
    GameUpdater(GameUpdater&&) noexcept = delete;
    GameUpdater& operator=(GameUpdater&&) noexcept = delete;
};
