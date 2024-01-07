#include "../../include/files/FileManager.hpp"
#include "../../include/files/FileUtils.hpp"

PlayerProgress FileManager::getDefaultPlayerProgress() { return {{0, 0}, 0}; }

Control FileManager::getDefaultControl() {
    return {
        InputData(sf::Keyboard::W),
        InputData(sf::Keyboard::S),
        InputData(sf::Keyboard::A),
        InputData(sf::Keyboard::D),
        InputData(sf::Keyboard::Space),
        InputData(sf::Mouse::Button::Left)
        };
}

bool FileManager::hasDataFiles() const {
    return FileUtils::hasDirectory(_game_data_path) && FileUtils::hasDirectory(_img_path) &&
        FileUtils::hasDirectory(_font_path);
}

bool FileManager::hasProgress() const { return FileUtils::hasRegularFile(_progress_path); }
bool FileManager::hasControl() const { return FileUtils::hasRegularFile(_control_path); }

void FileManager::deleteProgressFile() const { if (hasProgress()) { std::filesystem::remove(_progress_path); } }

void FileManager::save(const PlayerProgress& player_progress) const {
    FileUtils::saveDataToFile(_progress_path, &player_progress, sizeof player_progress);
}

void FileManager::loadOrGetDefault(PlayerProgress& player_progress) const noexcept(false) {
    if (hasProgress())
        FileUtils::loadDataFromFile(_progress_path, &player_progress, sizeof player_progress);
    else 
        player_progress = getDefaultPlayerProgress();
}

void FileManager::save(const Control& control) const noexcept(false) {
    FileUtils::saveDataToFile(_control_path, &control, sizeof control);
}

void FileManager::loadOrGetDefault(Control& control) const noexcept(false) {
    if (hasControl())
        FileUtils::loadDataFromFile(_control_path, &control, sizeof control);
    else
        control = getDefaultControl();
}