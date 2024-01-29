#include "../../../../../include/game/construction/game field creation/portal/PortalCreator.hpp"

void PortalCreator::createPortal(const sf::Vector2f& p, const float angle, const PortalInfo& portal_info) const {
    _game_field->quadtree_el.insert(_element_creator->create({
        p, angle, ElementType::PORTAL, portal_info.num, portal_info.scale}, portal_info.offset_factor));  
}

PortalCreator::PortalCreator(ElementCreator& element_creator, GameField& game_field,
        const InOutPortalInfo& in_out_portal_info):
    _element_creator(&element_creator), _game_field(&game_field), _in_out_portal_info(&in_out_portal_info) { }

void PortalCreator::createInPortal(const sf::Vector2f& p, const float angle) const {
    createPortal(p, angle, _in_out_portal_info->in_portal_info);    
}

void PortalCreator::createOutPortal(const sf::Vector2f& p, const float angle) const {
    createPortal(p, angle, _in_out_portal_info->out_portal_info);
}