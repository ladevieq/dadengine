#pragma once

#include <cstdint>

#include <vector>
#include <filesystem>

namespace DadEngine {
    std::vector<uint8_t> ReadFile(std::filesystem::path _filePath);
}
