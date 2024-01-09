// ReSharper disable CppIncompleteSwitchStatement CppDefaultCaseNotHandledInSwitchStatement CppClangTidyClangDiagnosticSwitch
#include <SFML/Window/Event.hpp>
#include "../../include/game/ChooseCharacterManager.hpp"
#include "../../include/additionally/AdditionalFunc.hpp"
#include "../../include/additionally/PixelConverter.hpp"
#include "../../include/geometry/SizeUtils.hpp"

sf::Vector2f ChooseCharacterManager::getSpriteScale() const {
    const auto& scale = (*_character_infos)[getSpriteIndex()].scale;
    return {
        scale.x * PixelConverter::convertWidthToCurrentScreen(SCALE_MULTIPLIER),
        scale.y * PixelConverter::convertHeightToCurrentScreen(SCALE_MULTIPLIER)
    };
}

size_t& ChooseCharacterManager::getSpriteIndex() const {
    return _game_context->player_progress.player_inventory.character_num;
}

void ChooseCharacterManager::setSpriteParameters() {
    const auto& animated_sprite(_sprites[getSpriteIndex()]);
    
    const sf::Vector2f size(animated_sprite.getWidth(), animated_sprite.getHeight());
    const auto scale(getSpriteScale());
    const auto scaled_half_size(SizeUtils::getScaledSize(size, scale) / 2.0f);
    const auto y_start = static_cast<float>(_game_context->window.getSize().y) / Y_START_FACTOR;
    
    _sprite.setOrigin(size / 2.0f);
    _sprite.setPosition(_sprite.getPosition().x, y_start - scaled_half_size.y);
    _sprite.setScale(scale);
}

void ChooseCharacterManager::fillSprite(const int delta_time) {
    auto& animated_sprite(_sprites[getSpriteIndex()]);
    if (animated_sprite != _sprite)
        setSpriteParameters();
    
    animated_sprite.changeState(delta_time);
    animated_sprite.setTextureToSprite(_sprite);
}

void ChooseCharacterManager::setButtonPositions() {
    const auto window_size = _game_context->window.getSize();
    const float x_center = static_cast<float>(window_size.x) / 2.0f;
    const float y_start = static_cast<float>(window_size.y) / Y_START_FACTOR;
    const float button_spacing(PixelConverter::convertHeightToCurrentScreen(BUTTON_SPACING));
    const float button_x_indent(PixelConverter::convertWidthToCurrentScreen(BUTTON_X_INDENT));
    
    _sprite.setPosition(x_center, y_start);
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
        if (auto& index = getSpriteIndex(); index > 0)
            --index;
        else
            index = _sprites.size() - 1;
    }, button_colors);
    _buttons.addButtonWidthOriginCenter(">", [this] {
        if (auto& index = getSpriteIndex(); index < _sprites.size() - 1)
            ++index;
        else
            index = 0;
    }, button_colors);
    _buttons.addButtonWidthOriginCenter("START", [this]{_game_state = nullptr;}, button_colors);
    _buttons.addButtonWidthOriginCenter("RETURN", [this]{*_game_state = GameState::RETURN_TO_MENU; _game_state = nullptr;}, button_colors);
}

void ChooseCharacterManager::draw(const int delta_time) {
    auto& window = _game_context->window;
    
    window.clear(_background_color);
    fillSprite(delta_time);
    window.draw(_sprite);
    _buttons.draw(window);
    window.display();
}

void ChooseCharacterManager::processKeyPressed(const sf::Keyboard::Key key) {
    switch (key) {
    case FullscreenToggler::DEFAULT_KEYBOARD_SWITCH:
        _game_context->fullscreen_toggler.toggleFullscreen(_cursors->normal_cursor);
        break;
    case sf::Keyboard::Escape:
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
        _game_context(&game_context), _sprites(std::move(sprites)), _character_infos(&character_infos),
        _buttons(font), _cursors(&cursors), _background_color(colors.background_color){
    createButtons(colors.button_colors);
    setButtonPositions();
    setSpriteParameters();
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