#pragma once
#include "PortalInfo.hpp"
#include "../../../GameField.hpp"
#include "../../../../element/ElementCreator.hpp"

class PortalCreator final {
    ElementCreator *_element_creator;
    GameField *_game_field;
    const InOutPortalInfo *_in_out_portal_info;

    void createPortal(const sf::Vector2f &p, const float angle, const PortalInfo &portal_info) const;
public:
    PortalCreator(ElementCreator &element_creator, GameField &game_field, const InOutPortalInfo &in_out_portal_info);

    void createInPortal(const sf::Vector2f &p, const float angle) const;
    void createOutPortal(const sf::Vector2f &p, const float angle) const;
    
    ~PortalCreator() noexcept = default;
    PortalCreator(PortalCreator&&) noexcept = delete;
    PortalCreator& operator=(PortalCreator&&) noexcept = delete;
    PortalCreator(const PortalCreator&) noexcept = delete;
    PortalCreator& operator=(const PortalCreator&) noexcept = delete;
};
