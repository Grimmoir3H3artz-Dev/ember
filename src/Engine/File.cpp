#include "Engine/File.hpp"

#include <fstream>
#include <sstream>
#include <stdexcept>

namespace Ember {

std::filesystem::path assetPath(std::string_view relative)
{
    std::filesystem::path rooted = std::filesystem::path(EMBER_ASSETS_PATH) / relative;
    if (std::filesystem::exists(rooted)) {
        return rooted;
    }

    std::filesystem::path nextToExe = std::filesystem::current_path() / "assets" / relative;
    if (std::filesystem::exists(nextToExe)) {
        return nextToExe;
    }

    return rooted;
}

std::string readTextFile(const std::filesystem::path& path)
{
    std::ifstream in(path, std::ios::binary);
    if (!in) {
        throw std::runtime_error("Failed to open file: " + path.string());
    }
    std::ostringstream ss;
    ss << in.rdbuf();
    return ss.str();
}

} // namespace Ember
