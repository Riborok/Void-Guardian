#include "../../include/files/FileManager.hpp"
#include "../../include/files/FileUtils.hpp"

bool FileManager::hasDataFiles() const {
    return FileUtils::hasDirectory(_game_data_path) && FileUtils::hasDirectory(_img_path);
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
        player_progress = _default_player_progress;
}

void FileManager::save(const Control& control) const noexcept(false) {
    FileUtils::saveDataToFile(_progress_path, &control, sizeof control);
}

void FileManager::loadOrGetDefault(Control& control) const noexcept(false) {
    if (hasControl())
        FileUtils::loadDataFromFile(_progress_path, &control, sizeof control);
    else
        control = _default_control;
}