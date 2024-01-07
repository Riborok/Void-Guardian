#include "../../include/additionally/AdditionalFunc.hpp"
#include <cstdlib>
#include <iomanip>
#include <sstream>

std::string AdditionalFunc::roundNum(const float num, const std::streamsize &precision_factor) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(precision_factor) << num;
    return oss.str();
}

inline std::string getCommand() {
    #ifdef _WIN32
        return "start";
    #elif __APPLE__
        return "open";
    #elif __linux__
        return "xdg-open";
    #else
        return "";
    #endif
}

void AdditionalFunc::openUrl(const std::string& url) {
    if (const std::string command = getCommand(); !command.empty()) {
        const std::string full_command = command + " " + url;
        system(full_command.c_str());
    }
}

void AdditionalFunc::setDefaultView(sf::RenderWindow& window) { window.setView(window.getDefaultView()); }