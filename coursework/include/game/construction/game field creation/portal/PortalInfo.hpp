#pragma once
#include <SFML/System/Vector2.hpp>

struct PortalInfo final {
    sf::Vector2f offset_factor;
    sf::Vector2f scale;
    size_t num;
    PortalInfo(const sf::Vector2f& offset_factor, const sf::Vector2f& scale, const size_t num):
        offset_factor(offset_factor), scale(scale), num(num) {}
};

struct InOutPortalInfo final {
    PortalInfo in_portal_info;
    PortalInfo out_portal_info;
    InOutPortalInfo(const PortalInfo &in_portal_info, const PortalInfo &out_portal_info):
        in_portal_info(in_portal_info), out_portal_info(out_portal_info) {}
};