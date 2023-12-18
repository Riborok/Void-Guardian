// ReSharper disable CppIncompleteSwitchStatement CppDefaultCaseNotHandledInSwitchStatement
#include "../../../../../include/game/construction/game field creation/arena/ArenaCreator.hpp"

ArenaCreator::ArenaCreator(const BoundaryCreator& boundary_creator, SpawnMapCreator &&spawn_map_creator):
    _boundary_creator(&boundary_creator), _spawn_map_creator(spawn_map_creator) { }

void ArenaCreator::createSpawns(Field& field, const int spawn_count) const {
    const auto& last_index = field.getLastIndex();
    const int attempt_count = std::max(last_index.x, last_index.y);
    std::uniform_int_distribution<int> random_x(0, last_index.x);
    std::uniform_int_distribution<int> random_y(0, last_index.y);
    
    for (int i = 0; i < spawn_count; ++i) {
        sf::Vector2i pos;
        int attempt = 0;
        do {
            pos = { RandomGenerator::getRandom(random_x), RandomGenerator::getRandom(random_y) };
            ++attempt;
        } while (field.get(pos) != CellType::EMPTY && attempt <= attempt_count);

        if (field.get(pos) == CellType::EMPTY)
            field.set(CellType::SPAWN, pos);
    }
}

void ArenaCreator::verifyEndCoord(sf::Vector2i& end_coord, const sf::Vector2i& last_index) {
    end_coord.x = std::max(0, std::min(end_coord.x, last_index.x));
    end_coord.y = std::max(0, std::min(end_coord.y, last_index.y));
}

void ArenaCreator::createWalls(Field& field, const int wall_count) const {
    const auto& last_index = field.getLastIndex();
    std::uniform_int_distribution<int> random_x(0, last_index.x);
    std::uniform_int_distribution<int> random_y(0, last_index.y);

    std::uniform_int_distribution<int> random_width(-last_index.x / 3, last_index.x / 3);
    std::uniform_int_distribution<int> random_height(-last_index.y / 3, last_index.y / 3);

    for (int i = 0; i < wall_count;) {
        const sf::Vector2i start_coord { RandomGenerator::getRandom(random_x), RandomGenerator::getRandom(random_y) };
        
        sf::Vector2i end_coord { start_coord.x + RandomGenerator::getRandom(random_width),
            start_coord.y + RandomGenerator::getRandom(random_height) };
        verifyEndCoord(end_coord, last_index);
        
        createWallSegment(field, start_coord, end_coord);
        i += (std::abs(end_coord.x - start_coord.x) + 1) * (std::abs(end_coord.y - start_coord.y) + 1);
    }
}

void ArenaCreator::createWallSegment(Field &field, const sf::Vector2i& start, const sf::Vector2i& end) const {
    const auto [min_x, max_x] = std::minmax(start.x, end.x);
    const auto [min_y, max_y] = std::minmax(start.y, end.y);

    for (int x = min_x; x <= max_x; ++x)
        for (int y = min_y; y <= max_y; ++y)
            field.set(CellType::WALL, {x, y});
}

sf::Vector2i ArenaCreator::getLastIndex(const Location& location) const {
    const auto& points = location.getPolygon().getPoints();
    const auto& size = _boundary_creator->getDelta();

    const int count_x = static_cast<int>((points[1].x - points[0].x)) / size.x - 2 * INDENT;
    const int count_y = static_cast<int>((points[3].y - points[0].y)) / size.y - 2 * INDENT;
    return {count_x, count_y};
}

sf::Vector2f ArenaCreator::transferPos(const sf::Vector2f &start_pos, const sf::Vector2i &size, const sf::Vector2i &pos) {
    return {
        start_pos.x + static_cast<float>(size.x * (pos.x + INDENT)),
        start_pos.y + static_cast<float>(size.y * (pos.y + INDENT))
    };
}

void ArenaCreator::createArena(const Field &field, SpawnPoints& spawn_points,
        const sf::Vector2f &start_pos, const sf::Vector2i &size) const {
    const sf::Vector2i& last_index = field.getLastIndex();

    for (sf::Vector2i index = {0, 0}; index.x <= last_index.x; ++index.x) {
        for (; index.y <= last_index.y; ++index.y) {
            switch (field.get(index)) {
            case CellType::WALL:
                _boundary_creator->createBlock(transferPos(start_pos, size, index));
                break;
            case CellType::SPAWN:
                spawn_points.push_back(transferPos(start_pos, size, index));
                break;
            }
        }
        index.y = 0;
    }
}

void ArenaCreator::create(const Location& location) const {
    Field field(getLastIndex(location), CellType::EMPTY);
    const int square = static_cast<int>(field.getTotalCount());
    
    const int wall_count = square / RandomGenerator::getRandom(_random_wall_count_denominator);
    const int spawn_count = square / RandomGenerator::getRandom(_random_spawn_count_denominator);
    
    createWalls(field, wall_count);
    createSpawns(field, spawn_count);
    createArena(field, _spawn_map_creator.installLocation(location),
        location.getPolygon().getPoints()[0], _boundary_creator->getDelta());
}