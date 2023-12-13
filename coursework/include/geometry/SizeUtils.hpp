#pragma once
#include <SFML/System/Vector2.hpp>
#include "../element/Element.hpp"

namespace SizeUtils {
    sf::Vector2i getScaledSize(const sf::Vector2i &size, const sf::Vector2f &scale);
    sf::Vector2f getScaledSize(const sf::Vector2f &size, const sf::Vector2f &scale);
    sf::Vector2f getWidthVector(const Element &element);
}
