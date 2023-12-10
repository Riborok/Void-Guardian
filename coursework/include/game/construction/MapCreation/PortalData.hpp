#pragma once
#include <SFML/System/Vector2.hpp>

struct PortalData final {
    sf::Vector2f portal_offset;
    sf::Vector2f scale;
    int num;
    PortalData(const sf::Vector2f& portal_offset, const sf::Vector2f& scale, const int num):
        portal_offset(portal_offset), scale(scale), num(num) {}
};

struct InOutPortals final {
    PortalData in_portal;
    PortalData out_portal;
    InOutPortals(const PortalData &in_portal, const PortalData &out_portal):
        in_portal(in_portal), out_portal(out_portal) {}
};