#pragma once
#include <string>
#include <SFML/Graphics/RenderWindow.hpp>

namespace AdditionalFunc {
    /**
     * Rounds the value to a string representation with the specified precision.
     * The precision factor controls the number of digits after the decimal point in the resulting string.
     * @param num The value to be rounded.
     * @param precision_factor The precision factor determining the number of decimal places in the result.
     * @return A string representation of the rounded value.
     */
    std::string roundNum(const float num, const std::streamsize &precision_factor);

    /**
     * Opens the specified URL in the default web browser based on the operating system.
     * @param url The URL to be opened.
     */
    void openUrl(const std::string& url);

    void setDefaultView(sf::RenderWindow &window);
}
