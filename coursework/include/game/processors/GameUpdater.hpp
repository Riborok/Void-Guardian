#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

#include "../WindowParam.hpp"
#include "../../geometry/collision/ElementCollisionSet.hpp"
#include "../../model/polygon/Polygon.hpp"
#include "../../Quadtree/QuadtreeTypeDefs/QuadtreeEl.hpp"

class GameUpdater final {
    const Polygon *_focus;
    sf::RenderWindow *_window;
    QuadtreeEl *_quadtree;
    
    ElementCollisionSet _elements;
    WindowParam _window_param;

    void setParameters(const sf::Vector2f &focus);
    void updateView(const sf::Vector2f &focus);
public:
    GameUpdater(const Polygon &focus, sf::RenderWindow &window, QuadtreeEl &quadtree);
    
    void update();
    const ElementCollisionSet &getCollidedElements() const;
    WindowParam &getWindowParam();
    void removeElement(const Element* element);
    
    ~GameUpdater() noexcept = default;
    
    GameUpdater(const GameUpdater&) noexcept = delete;
    GameUpdater& operator=(const GameUpdater&) noexcept = delete;
    GameUpdater(GameUpdater&&) noexcept = delete;
    GameUpdater& operator=(GameUpdater&&) noexcept = delete;
};
