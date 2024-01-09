#pragma once
#include <SFML/System/Vector2.hpp>

struct PortalData final {
    sf::Vector2f offset_factor;
    sf::Vector2f scale;
    size_t num;
    PortalData(const sf::Vector2f& offset_factor, const sf::Vector2f& scale, const size_t num):
        offset_factor(offset_factor), scale(scale), num(num) {}
};

struct InOutPortals final {
    PortalData in_portal;
    PortalData out_portal;
    InOutPortals(const PortalData &in_portal, const PortalData &out_portal):
        in_portal(in_portal), out_portal(out_portal) {}
};