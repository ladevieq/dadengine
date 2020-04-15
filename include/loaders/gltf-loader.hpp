#pragma once

#include <filesystem>
#include <vector>

namespace DadEngine
{
    class Mesh;

    std::vector<Mesh> LoadGLTF(std::filesystem::path &_path);
} // namespace DadEngine
