#include "../../../include/game/choose character/CharacterText.hpp"

#include "../../../include/additionally/AdditionalFunc.hpp"
#include "../../../include/additionally/PixelConverter.hpp"

CharacterText::Texts CharacterText::getTexts(const sf::Font& font) {
    const unsigned text_size(PixelConverter::convertHeightToCurrentScreen(TEXT_SIZE));
    return {
        {"", font, text_size},
        {"", font, text_size},
        {"", font, text_size},
        {"", font, text_size}
    };
}

void CharacterText::fillText(const CharacterInfo& character_info) {
    _texts[0].setString("Health: " + std::to_string(character_info.entity_info.health));
    _texts[1].setString("Armor: " + std::to_string(character_info.entity_info.armor));
    _texts[2].setString("Armor Strength: " + AdditionalFunc::roundNum(character_info.entity_info.armor_strength, PRECISION_FACTOR));
    _texts[3].setString("Speed: " + AdditionalFunc::roundNum(character_info.info.speed, PRECISION_FACTOR));
}

void CharacterText::draw(sf::RenderWindow &window) const {
    for (const auto& text : _texts)
        window.draw(text);
}

void CharacterText::setPosition(sf::Vector2f point, const float y_indent) {
    for (auto& text : _texts) {
        text.setPosition(point);
        point.y += y_indent;
    }
}