#pragma once
#include <SFML/Window/Keyboard.hpp>

struct Control final {
    sf::Keyboard::Key move;
    sf::Keyboard::Key shoot;
    Control(const sf::Keyboard::Key move, const sf::Keyboard::Key shoot): move(move), shoot(shoot) { }
};
