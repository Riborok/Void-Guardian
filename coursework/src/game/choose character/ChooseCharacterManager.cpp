// ReSharper disable CppIncompleteSwitchStatement CppDefaultCaseNotHandledInSwitchStatement CppClangTidyClangDiagnosticSwitch
#include <SFML/Window/Event.hpp>
#include "../../../include/game/choose character/ChooseCharacterManager.hpp"
#include "../../../include/additionally/AdditionalFunc.hpp"
#include "../../../include/additionally/PixelConverter.hpp"
#include "../../../include/geometry/SizeUtils.hpp"
#include "../../../include/gui/ReservedKeys.hpp"

size_t& ChooseCharacterManager::getSpriteIndex() const {
    return _game_context->player_progress.player_inventory.character_num;
}

void ChooseCharacterManager::setPositions() {
    const auto window_size = _game_context->window.getSize();
    const float x_center = static_cast<float>(window_size.x) / 2.0f;
    const float y_start = static_cast<float>(window_size.y) / Y_START_FACTOR;
    const float button_spacing(PixelConverter::convertHeightToCurrentScreen(BUTTON_SPACING));
    const float button_x_indent(PixelConverter::convertWidthToCurrentScreen(BUTTON_X_INDENT));

    _character_visualization.setPositions(x_center, y_start, button_spacing);
    
    _buttons.setPos(0, {x_center - button_x_indent, y_start});
    _buttons.setPos(1, {x_center + button_x_indent, y_start});
    const size_t count = _buttons.getCount();
    float curr_y = y_start + button_spacing;
    for (size_t i = 2; i < count; ++i) {
        _buttons.setPos(i, {x_center, curr_y});
        curr_y += button_spacing;
    }
}

void ChooseCharacterManager::createButtons(const ButtonColors& button_colors) {
    _buttons.addButtonWidthOriginCenter("<", [this] {
        if (auto& index = getSpriteIndex(); index > 0) { --index; }
        else                                                 { index = _character_visualization.getLastIndex(); }
    }, button_colors);
    _buttons.addButtonWidthOriginCenter(">", [this] {
        if (auto& index = getSpriteIndex(); index < _character_visualization.getLastIndex()) { ++index; }
        else                                                                   { index = 0; }
    }, button_colors);
    _buttons.addButtonWidthOriginCenter("START", [this]{_game_state = nullptr;}, button_colors);
    _buttons.addButtonWidthOriginCenter("RETURN", [this]{*_game_state = GameState::RETURN_TO_MENU; _game_state = nullptr;}, button_colors);
}

void ChooseCharacterManager::draw(const int delta_time) {
    auto& window = _game_context->window;
    
    window.clear(_background_color);
    _character_visualization.updateSprite(getSpriteIndex(), delta_time);
    _character_visualization.draw(window);
    _buttons.draw(window);
    window.display();
}

void ChooseCharacterManager::processKeyPressed(const sf::Keyboard::Key key) {
    switch (key) {
    case ReservedKeys::FULL_SCREEN_TOGGLE:
        _game_context->fullscreen_toggler.toggleFullscreen(_cursors->normal_cursor);
        break;
    case ReservedKeys::BACK:
        *_game_state = GameState::RETURN_TO_MENU;
        _game_state = nullptr;
        break;
    }
}

void ChooseCharacterManager::processEvents() {
    auto& window = _game_context->window;
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::LostFocus:
            _game_loop_state.is_active = false;
            break;
        case sf::Event::GainedFocus:
            _game_loop_state.is_active = true;
            _game_loop_state.clock.restart();
            break;
        case sf::Event::KeyPressed:
            processKeyPressed(event.key.code);
            break;
        case sf::Event::MouseButtonReleased:
            _buttons.handleClick(window.mapPixelToCoords(sf::Mouse::getPosition(window)));    
            break;
        case sf::Event::MouseMoved:
            const auto buttons_res(_buttons.handleHoverTextColors(window.mapPixelToCoords(sf::Mouse::getPosition(window))));

            if (has(buttons_res, MouseMovedRes::SELECTION_CURSOR))
                window.setMouseCursor(_cursors->selection_cursor);
            else
                window.setMouseCursor(_cursors->normal_cursor);
            break;
        }
    }
}

ChooseCharacterManager::ChooseCharacterManager(GameContext& game_context, AnimatedSprites&& sprites,
        CharacterInfos &character_infos, const sf::Font& font, const Cursors& cursors, const Colors& colors):
        _game_context(&game_context), _character_visualization(std::move(sprites), character_infos, font),
        _buttons(font), _cursors(&cursors), _background_color(colors.background_color) {
    createButtons(colors.button_colors);
    setPositions();
    _character_visualization.setSpriteParameters(getSpriteIndex());
}

void ChooseCharacterManager::start(GameState& game_state) {
    _game_state = &game_state;
    AdditionalFunc::setDefaultView(_game_context->window);
    _buttons.setDefaultColor();
    
    _game_loop_state.clock.restart();
    while (_game_state && _game_context->window.isOpen()) {
        if (_game_loop_state.is_active)
            draw(_game_loop_state.clock.restart().asMilliseconds());
        processEvents();
    }
}