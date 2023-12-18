#pragma once
#include <map>
#include <vector>
#include <SFML/System/Vector2.hpp>

typedef std::vector<sf::Vector2f> SpawnPoints;
typedef std::map<size_t, SpawnPoints> SpawnMap;