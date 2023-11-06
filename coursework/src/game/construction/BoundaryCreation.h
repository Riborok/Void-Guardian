#pragma once
#include <SFML/System/Vector2.hpp>
#include <random>

#include "RectLoc.h"
#include "../../additionally/AdditionalFunc.h"
#include "../../element/ElementCreation.h"
#include "../../Quadtree/Quadtree.h"

namespace BoundaryCreation {
    namespace InnerLogic {
        std::uniform_int_distribution<int> missed_blocks_num(4, 9);
    
        inline unsigned insertHorBlocks(unsigned coord, const unsigned last, const unsigned y,
                const int num, const sf::Vector2f &scale, const unsigned delta, Quadtree<Element> &quadtree) {
            while (coord < last) {
                quadtree.insert(ElementCreation::create({static_cast<float>(coord), static_cast<float>(y)},
                    0, Types::ElementTypes::BLOCK, num, scale));
                coord += delta;
            }
            return coord;
        }
        inline unsigned insertHorMissedBlocks(unsigned coord, const unsigned last, const unsigned y,
                const sf::Vector2f &scale, const unsigned delta, RectLoc *rect_loc) {
            while (coord < last) {
                rect_loc->addBlock(ElementCreation::create({static_cast<float>(coord), static_cast<float>(y)},
                    0, Types::ElementTypes::BLOCK, AdditionalFunc::getRandom(missed_blocks_num), scale));
                coord += delta;
            }
            return coord;
        }
        
        inline unsigned insertVertBlocks(unsigned coord, const unsigned last, const unsigned x,
                const int num, const sf::Vector2f &scale, const unsigned delta, Quadtree<Element> &quadtree) {
            while (coord < last) {
                quadtree.insert(ElementCreation::create({static_cast<float>(x), static_cast<float>(coord)},
                    0, Types::ElementTypes::BLOCK, num, scale));
                coord += delta;
            }
            return coord;
        }
        inline unsigned insertVertMissedBlocks(unsigned coord, const unsigned last, const unsigned x,
                const sf::Vector2f &scale, const unsigned delta, RectLoc *rect_loc) {
            while (coord < last) {
                rect_loc->addBlock(ElementCreation::create({static_cast<float>(x), static_cast<float>(coord)},
                    0, Types::ElementTypes::BLOCK, AdditionalFunc::getRandom(missed_blocks_num), scale));
                coord += delta;
            }
            return coord;
        }
    }
    inline void createHorBoundary(const int num, const sf::Vector2u &p, const unsigned last, Quadtree<Element> &quadtree,
                                  RectLoc *rect_loc, const sf::Vector2f &scale,
                                  const unsigned delta, const unsigned offset) {
        unsigned coord = p.x;
        const unsigned last_offset = (p.x + last - offset) / 2;

        coord = InnerLogic::insertHorBlocks(coord, last_offset, p.y, num, scale, delta, quadtree);
        coord = InnerLogic::insertHorMissedBlocks(coord, coord + offset, p.y, scale, delta, rect_loc);
        InnerLogic::insertHorBlocks(coord, last, p.y, num, scale, delta, quadtree);
    }
    inline void createVertBoundary(const int num, const sf::Vector2u &p, const unsigned last, Quadtree<Element> &quadtree,
                                   RectLoc *rect_loc, const sf::Vector2f &scale,
                                   const unsigned delta, const unsigned offset) {
        unsigned coord = p.y;
        const unsigned last_offset = (p.y + last - offset) / 2;

        coord = InnerLogic::insertVertBlocks(coord, last_offset, p.x, num, scale, delta, quadtree);
        coord = InnerLogic::insertVertMissedBlocks(coord, coord + offset, p.x, scale, delta, rect_loc);
        InnerLogic::insertVertBlocks(coord, last, p.x, num, scale, delta, quadtree);
    }
}
