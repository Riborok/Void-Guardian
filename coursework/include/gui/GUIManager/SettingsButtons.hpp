// ReSharper disable CppClangTidyModernizeUseNodiscard
#pragma once
#include "../Buttons.hpp"
#include "../../game/entity/player/Control.hpp"
#include "../../game/input/InputData.hpp"

class SettingsButtons final {
    Control *_control;
    Buttons _buttons;
    sf::Color _pressed_color;
    int _active_index = -1;

    typedef std::vector<std::string> Strings;
    [[nodiscard]] Strings getActionNames() const;
public:
    SettingsButtons(Control &control, const sf::Font &font, const sf::Color pressed_color);
    void setActionNames();
    void setInputData(const InputData &input_data);
    void createButtons(bool& continue_settings, const ButtonColors &button_colors);
    void draw(sf::RenderWindow &render_window);
    void resetActiveIndex();
    void setDefaultColor();
    bool handleClick(const sf::Vector2f &mouse) const;
    void setPos(const size_t i, const sf::Vector2f &p);
    [[nodiscard]] bool hasActiveButton() const;
    MouseMovedRes handleHoverTextColors(const sf::Vector2f &position);

    ~SettingsButtons() noexcept = default;
    SettingsButtons(SettingsButtons&&) noexcept = default;
    SettingsButtons& operator=(SettingsButtons&&) noexcept = delete;
    SettingsButtons(const SettingsButtons&) noexcept = delete;
    SettingsButtons& operator=(const SettingsButtons&) noexcept = delete;
};