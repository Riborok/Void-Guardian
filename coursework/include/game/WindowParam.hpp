#pragma once
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Vector2.hpp>

class WindowParam final {
    sf::Vector2f _window_half_size;
    sf::View _view;
public:
    explicit WindowParam(const sf::Vector2f &size);
    
    const sf::Vector2f& getWindowHalfSize() const;
    const sf::View& getView() const;
    void updateSize(const sf::Vector2f &size);
    void setFocus(const sf::Vector2f &focus);

    ~WindowParam() noexcept = default;
    
    WindowParam(const WindowParam&) noexcept = delete;
    WindowParam& operator=(const WindowParam&) noexcept = delete;
    WindowParam(WindowParam&&) noexcept = delete;
    WindowParam& operator=(WindowParam&&) noexcept = delete;
};
