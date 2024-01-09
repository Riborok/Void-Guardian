#pragma once
#include <vector>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "../entity/InfoTables.hpp"

class CharacterText final {
    typedef std::vector<sf::Text> Texts;
    static constexpr std::streamsize PRECISION_FACTOR = 3;
    static constexpr unsigned TEXT_SIZE = 30;
    static Texts getTexts(const sf::Font &font);
    Texts _texts;
public:
    explicit CharacterText(const sf::Font &font): _texts(getTexts(font)) {}
    void fillText(const CharacterData &character_data);
    void draw(sf::RenderWindow &window) const;
    void setPosition(sf::Vector2f point, const float y_indent);

    ~CharacterText() noexcept = default;
    CharacterText(CharacterText&& other) noexcept = default;
    CharacterText& operator=(CharacterText&&) noexcept = delete;
    CharacterText(const CharacterText&) noexcept = delete;
    CharacterText& operator=(const CharacterText&) noexcept = delete;
};