#include "../../include/files/FileOperator.hpp"
#include "../../include/files/FileUtils.hpp"

PlayerProgress FileOperator::getDefaultPlayerProgress() { return {{0, 0}, 0}; }

Control FileOperator::getDefaultControl() {
    return {
        InputInfo(sf::Keyboard::W),
        InputInfo(sf::Keyboard::S),
        InputInfo(sf::Keyboard::A),
        InputInfo(sf::Keyboard::D),
        InputInfo(sf::Keyboard::Space),
        InputInfo(sf::Mouse::Button::Left)
        };
}

bool FileOperator::hasDataFiles() const {
    return FileUtils::hasDirectory(_app_data_path) && FileUtils::hasDirectory(_img_path) &&
        FileUtils::hasDirectory(_font_path);
}

bool FileOperator::hasProgress() const { return FileUtils::hasRegularFile(_progress_path); }
bool FileOperator::hasControl() const { return FileUtils::hasRegularFile(_control_path); }

void FileOperator::deleteProgressFile() const { if (hasProgress()) { std::filesystem::remove(_progress_path); } }

void FileOperator::save(const PlayerProgress& player_progress) const {
    FileUtils::saveDataToFile(_progress_path, &player_progress, sizeof player_progress);
}

void FileOperator::loadOrGetDefault(PlayerProgress& player_progress) const noexcept(false) {
    if (hasProgress())
        FileUtils::loadDataFromFile(_progress_path, &player_progress, sizeof player_progress);
    else 
        player_progress = getDefaultPlayerProgress();
}

void FileOperator::save(const Control& control) const noexcept(false) {
    FileUtils::saveDataToFile(_control_path, &control, sizeof control);
}

void FileOperator::loadOrGetDefault(Control& control) const noexcept(false) {
    if (hasControl())
        FileUtils::loadDataFromFile(_control_path, &control, sizeof control);
    else
        control = getDefaultControl();
}