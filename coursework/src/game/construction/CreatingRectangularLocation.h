#pragma once
#include <SFML/System/Vector2.hpp>

#include "../../element/ElementCreation.h"
#include "../../Quadtree/Quadtree.h"

namespace CreatingRectangularLocation {
    inline void createBackground(const int num, const sf::Vector2f &p0, const sf::Vector2f &p1,
            Quadtree &quadtree, const float scale) {
        const float dx = Constants::BACKGROUND_SIZE.x * scale, dy = Constants::BACKGROUND_SIZE.y * scale;
        
        float y = p0.y;
        while (y < p1.y) {
            float x = p0.x;
            while (x < p1.x) {
                quadtree.insert(ElementCreation::create({x, y}, 0, Types::ElementTypes::BACKGROUND, num, scale));
                x += dx;
            }
            y += dy;
        }
    }

    enum DoorOpening {
        NONE    =   0b0000,
        LEFT    =   0b0001,
        RIGHT   =   0b0010,
        TOP     =   0b0100,
        BOTTOM  =   0b1000,
    };
    
    namespace InnerLogic {
        inline float insertBlocks(float coord, const float last, const sf::Vector2f &p, const int num,
                const float scale, const float delta, Quadtree &quadtree, const bool is_horizontal) {
            while (coord < last) {
                sf::Vector2f position = is_horizontal ? sf::Vector2f(coord, p.y) : sf::Vector2f(p.x, coord);
                quadtree.insert(ElementCreation::create(position, 0, Types::ElementTypes::BLOCK, num, scale));
                coord += delta;
            }
            return coord;
        }
        inline void createBoundary(const int num, const sf::Vector2f &p, const float last, Quadtree &quadtree,
                const float scale, const float delta, const bool is_horizontal, const float offset) {
            float coord = is_horizontal ? p.x : p.y;
            const float last_offset = (coord + last - offset) / 2;

            coord = insertBlocks(coord, last_offset, p, num, scale, delta, quadtree, is_horizontal);
            coord += offset;
            insertBlocks(coord, last, p, num, scale, delta, quadtree, is_horizontal);
        }
        inline bool isLeft(const DoorOpening door_opening) { return door_opening & LEFT; }
        inline bool isRight(const DoorOpening door_opening) { return door_opening & RIGHT; }
        inline bool isTop(const DoorOpening door_opening) { return door_opening & TOP; }
        inline bool isBottom(const DoorOpening door_opening) { return door_opening & BOTTOM; }
    }
    
    inline void createBoundary(const int num, const sf::Vector2f &p0, const sf::Vector2f &p1,
            Quadtree &quadtree, const float scale, const DoorOpening door_opening, const float offset = 0) {
        const float dx = Constants::BLOCK_SIZE.x * scale, dy = Constants::BLOCK_SIZE.y * scale;
        const float start_y = p0.y + dy;
        const float last_y = p1.y - dy;
        const float last_x = p1.x - dx;

        InnerLogic::createBoundary(num, p0, p1.x, quadtree, scale, dx, true,
            InnerLogic::isTop(door_opening) ? offset : 0);
        InnerLogic::createBoundary(num, {p0.x, last_y}, p1.x, quadtree, scale, dx, true,
            InnerLogic::isBottom(door_opening) ? offset : 0);

        InnerLogic::createBoundary(num, {p0.x, start_y}, last_y, quadtree, scale, dy, false,
            InnerLogic::isLeft(door_opening) ? offset : 0);
        InnerLogic::createBoundary(num, {last_x, start_y}, last_y, quadtree, scale, dy, false,
            InnerLogic::isRight(door_opening) ? offset : 0);
    }
}
