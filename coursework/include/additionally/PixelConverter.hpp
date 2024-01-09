#pragma once
#include <SFML/Window/VideoMode.hpp>

namespace PixelConverter {
    static constexpr float FULL_HD_WIDTH = 1920;
    static constexpr float FULL_HD_HEIGHT = 1080;
    inline float convertWidthToCurrentScreen(const float pixel_count) {
        return static_cast<float>(sf::VideoMode::getDesktopMode().width) / FULL_HD_WIDTH * pixel_count;      
    }
    inline float convertHeightToCurrentScreen(const float pixel_count) {
        return static_cast<float>(sf::VideoMode::getDesktopMode().height) / FULL_HD_HEIGHT * pixel_count;    
    }
    inline unsigned convertWidthToCurrentScreen(const unsigned pixel_count) {
        return static_cast<unsigned>(convertWidthToCurrentScreen(static_cast<float>(pixel_count))); 
    }
    inline unsigned convertHeightToCurrentScreen(const unsigned pixel_count) {
        return static_cast<unsigned>(convertHeightToCurrentScreen(static_cast<float>(pixel_count)));
    }
}