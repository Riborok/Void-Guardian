#pragma once
#include "PortalData.hpp"
#include "../../../GameField.hpp"
#include "../../../../element/ElementCreator.hpp"

class PortalCreator final {
    ElementCreator *_element_creator;
    GameField *_game_field;
    const InOutPortals *_in_out_portals;

    void createPortal(const sf::Vector2f &p, const float angle, const PortalData &portal_data) const;
public:
    PortalCreator(ElementCreator &element_creator, GameField &game_field, const InOutPortals &in_out_portals);

    void createInPortal(const sf::Vector2f &p, const float angle) const;
    void createOutPortal(const sf::Vector2f &p, const float angle) const;
    
    ~PortalCreator() noexcept = default;
    PortalCreator(PortalCreator&&) noexcept = delete;
    PortalCreator& operator=(PortalCreator&&) noexcept = delete;
    PortalCreator(const PortalCreator&) noexcept = delete;
    PortalCreator& operator=(const PortalCreator&) noexcept = delete;
};
