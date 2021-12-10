#include "engine/utils/File.h"

namespace File
{
    auto Read(const std::string& path) -> std::string
    {
        auto file = std::ifstream(path, std::ifstream::in);
        ASSERT(file, "Failed to open file: " + path + "!");

        auto stream = std::stringstream();
        stream << file.rdbuf();
    
        return stream.str();
    }
}