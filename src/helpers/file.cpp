#include "file.hpp"

#include <fstream>
#include <iostream>

namespace DadEngine {
    std::vector<uint8_t> ReadFile(std::filesystem::path _filePath) {
        std::fstream fs(_filePath, std::ios::in | std::ios::binary);

        if (!fs.good())
        {
            std::cout << "File : " << _filePath.string() << " failed to open !\n";
            return {};
        }

        std::streampos begin = fs.tellg();

        fs.seekg(0, std::ios::end);
        std::streampos end = fs.tellg();

        std::vector<uint8_t> buffer(static_cast<size_t>(end - begin));

        fs.seekg(0, std::ios::beg);
        fs.read(reinterpret_cast<char*>(buffer.data()), end - begin);

        fs.close();

        buffer.push_back('\0');

        return buffer;
    }
}
