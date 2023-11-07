#include "../../../include/model/polygon/ManipulationOfPolygon.hpp"

#include "../../../include/geometry/Trigonometry.hpp"
#include "../../../include/geometry/Vector2Rotation.hpp"

namespace ManipulationOfPolygon {
    void movePolygon(Polygon &polygon, const sf::Vector2f &vector) {
        for (auto &point : polygon.points())
            point += vector;
    }

    void rotatePolygon(Polygon &polygon, const float delta_angle) {
        const float sin = Trigonometry::sinDegrees(delta_angle);
        const float cos = Trigonometry::cosDegrees(delta_angle);
        const sf::Vector2f center = polygon.calcCenter();
        
        for (auto &point : polygon.points())
            Vector2Rotation::rotateVector2AroundTarget(point, center, sin, cos);
    }
}
