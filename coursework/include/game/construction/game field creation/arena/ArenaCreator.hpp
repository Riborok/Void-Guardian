#pragma once
#include "CellType.hpp"
#include "../../BoundaryCreator.hpp"
#include "../../../../additionally/2DArray/Array2D.hpp"
#include "enemy spawn/SpawnMapCreator.hpp"

class ArenaCreator final {
    typedef Array2D<CellType> Field;
    static constexpr int INDENT = 2;

    mutable std::uniform_int_distribution<int> _random_wall_count_denominator{2, 4};
    mutable std::uniform_int_distribution<int> _random_spawn_count_denominator{4, 6};
    
    const BoundaryCreator *_boundary_creator;
    SpawnMapCreator _spawn_map_creator;
    sf::Vector2i getLastIndex(const Location& location) const;
    void createSpawns(Field& field, const int spawn_count) const;
    void createWalls(Field& field, const int wall_count) const;
    void createWallSegment(Field &field, const sf::Vector2i& start, const sf::Vector2i& end) const;
    void createArena(const Field &field, SpawnPoints& spawn_points, const sf::Vector2f &start_pos, const sf::Vector2i &size) const;
    static void verifyEndCoord(sf::Vector2i& end_coord, const sf::Vector2i& last_index);
    static sf::Vector2f transferPos(const sf::Vector2f &start_pos, const sf::Vector2i &size, const sf::Vector2i &pos);
public:
    ArenaCreator(const BoundaryCreator &boundary_creator, SpawnMapCreator &&spawn_map_creator);

    void create(const Location& location) const;
    
    ~ArenaCreator() noexcept = default;
    ArenaCreator(ArenaCreator&&) noexcept = delete;
    ArenaCreator& operator=(ArenaCreator&&) noexcept = delete;
    ArenaCreator(const ArenaCreator&) noexcept = delete;
    ArenaCreator& operator=(const ArenaCreator&) noexcept = delete;
};
