#include <filesystem>
#include <fstream>
#include "../../include/files/FileUtils.hpp"

bool FileUtils::hasDirectory(const std::filesystem::path& file_path) {
    return exists(file_path) && is_directory(file_path);
}

bool FileUtils::hasRegularFile(const std::filesystem::path& file_path) {
    return exists(file_path) && is_regular_file(file_path);
}

void FileUtils::saveDataToFile(const std::filesystem::path& file_path, const void* data, const size_t size) {
    if (std::ofstream file(file_path, std::ios::out | std::ios::binary); file.is_open()) {
        std::vector<char> data_buffer(size);
        std::memcpy(data_buffer.data(), data, size);

        file.write(data_buffer.data(), static_cast<std::streamsize>(data_buffer.size()));

        file.close();
    } else
        throw std::runtime_error("Unable to open file '" + file_path.string() + "' for writing");
}

void FileUtils::loadDataFromFile(const std::filesystem::path& file_path, void* data, const size_t size) {
    if (std::ifstream file(file_path, std::ios::in | std::ios::binary); file.is_open()) {
        std::vector<char> data_buffer(size);

        file.read(data_buffer.data(), static_cast<std::streamsize>(data_buffer.size()));
        file.close();

        std::memcpy(data, data_buffer.data(), size);
    }
    else
        throw std::runtime_error("Unable to open file '" + file_path.string() + "' for reading");
}