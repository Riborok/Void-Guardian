#pragma once
#include <filesystem>
#include "PlayerProgress.hpp"
#include "../game/entity/player/Control.hpp"

class FileManager final {
    const std::filesystem::path _game_data_path = "./AppData";
    const std::filesystem::path _img_path = _game_data_path / "img";
    const std::filesystem::path _font_path = _game_data_path / "font";
    const std::filesystem::path _progress_path = _game_data_path / "progress";
    const std::filesystem::path _control_path = _game_data_path / "control";

    static PlayerProgress getDefaultPlayerProgress();
    static Control getDefaultControl();
public:
    [[nodiscard]] bool hasDataFiles() const;
    [[nodiscard]] bool hasProgress() const;
    [[nodiscard]] bool hasControl() const;
    void deleteProgressFile() const;
    
    void save(const PlayerProgress& player_progress) const noexcept(false);
    void loadOrGetDefault(PlayerProgress& player_progress) const noexcept(false);

    void save(const Control& control) const noexcept(false);
    void loadOrGetDefault(Control& control) const noexcept(false);

    FileManager() noexcept = default;
    ~FileManager() noexcept = default;
    FileManager(const FileManager&) noexcept = delete;
    FileManager& operator=(const FileManager&) noexcept = delete;
    FileManager(FileManager&&) noexcept = default;
    FileManager& operator=(FileManager&&) noexcept = delete;
};