#pragma once

#include <cstdint>

#include <filesystem>
#include <vector>

namespace DadEngine
{
    std::vector<uint8_t> ReadFile(std::filesystem::path _fullpath);
}
