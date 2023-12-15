#pragma once

namespace FileUtils {
    bool hasDirectory(const std::filesystem::path &file_path);
    bool hasRegularFile(const std::filesystem::path &file_path);

    void saveDataToFile(const std::filesystem::path &file_path, const void* data, const size_t size) noexcept(false);
    void loadDataFromFile(const std::filesystem::path &file_path, void* data, const size_t size) noexcept(false);
}