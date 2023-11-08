#include "../../../include/game/construction/LocationCreation.hpp"

#include "../../../include/additionally/Constants.hpp"

Location *LocationCreation::create(const int x0, const int y0, const int x1, const int y1) {
    return new Location(
        Rectangle(static_cast<float>(x0), static_cast<float>(y0),
            static_cast<float>(x1), static_cast<float>(y1)),
        Constants::id_tracker.generate(LOCATION));
}