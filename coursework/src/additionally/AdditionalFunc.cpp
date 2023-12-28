#include "../../include/additionally/AdditionalFunc.hpp"
#include <cstdlib>
#include <iomanip>
#include <sstream>

std::string AdditionalFunc::roundNum(const float num, const std::streamsize &precision_factor) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(precision_factor) << num;
    return oss.str();
}

void AdditionalFunc::openUrl(const std::string& url) {
    #ifdef _WIN32
        const std::string command = "start";
    #elif __APPLE__
        const std::string command = "open";
    #elif __linux__
        const std::string command = "xdg-open";
    #else
        return;
    #endif

    const std::string full_command = command + " " + url;
    system(full_command.c_str());
}