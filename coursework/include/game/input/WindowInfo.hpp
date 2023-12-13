#pragma once
#include <string>

struct WindowInfo final {
    std::string title;
    std::string icon_src;
    WindowInfo(std::string window_title, std::string window_icon_src):
        title(std::move(window_title)), icon_src(std::move(window_icon_src)) {}
};
