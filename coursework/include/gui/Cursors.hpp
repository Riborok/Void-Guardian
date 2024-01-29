#pragma once
#include <SFML/Window/Cursor.hpp>

struct Cursors final {
    sf::Cursor normal_cursor;
    sf::Cursor selection_cursor;
    Cursors() {
        normal_cursor.loadFromSystem(sf::Cursor::Arrow);
        selection_cursor.loadFromSystem(sf::Cursor::Hand);
    }
};