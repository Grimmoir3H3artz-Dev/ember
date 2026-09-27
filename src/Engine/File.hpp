#pragma once

#include <filesystem>
#include <string>
#include <string_view>

namespace Ember {

std::filesystem::path assetPath(std::string_view relative);
std::string readTextFile(const std::filesystem::path& path);

} // namespace Ember
