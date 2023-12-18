#include "../../../../../include/game/construction/game field creation/portal/PortalCreator.hpp"

void PortalCreator::createPortal(const sf::Vector2f& p, const float angle, const PortalData& portal_data) const {
    _game_field->quadtree_el.insert(_element_creator->create({
        p, angle, ElementType::PORTAL, portal_data.num, portal_data.scale}, portal_data.portal_offset));  
}

PortalCreator::PortalCreator(ElementCreator& element_creator, GameField& game_field,
        const InOutPortals& in_out_portals):
    _element_creator(&element_creator), _game_field(&game_field), _in_out_portals(&in_out_portals) { }

void PortalCreator::createInPortal(const sf::Vector2f& p, const float angle) const {
    createPortal(p, angle, _in_out_portals->in_portal);    
}

void PortalCreator::createOutPortal(const sf::Vector2f& p, const float angle) const {
    createPortal(p, angle, _in_out_portals->out_portal);
}