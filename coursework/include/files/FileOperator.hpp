#pragma once
#include <filesystem>
#include "PlayerProgress.hpp"
#include "../game/entity/player/Control.hpp"

class FileOperator final {
    const std::filesystem::path _app_data_path = "./AppData";
    const std::filesystem::path _img_path = _app_data_path / "img";
    const std::filesystem::path _font_path = _app_data_path / "font";
    const std::filesystem::path _progress_path = _app_data_path / "progress";
    const std::filesystem::path _control_path = _app_data_path / "control";

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

    FileOperator() noexcept = default;
    ~FileOperator() noexcept = default;
    FileOperator(const FileOperator&) noexcept = delete;
    FileOperator& operator=(const FileOperator&) noexcept = delete;
    FileOperator(FileOperator&&) noexcept = default;
    FileOperator& operator=(FileOperator&&) noexcept = delete;
};