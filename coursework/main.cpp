#include "include/Launcher.hpp"

void main() {
    auto* launcher = new Launcher;
    launcher->start();
    delete launcher;
}