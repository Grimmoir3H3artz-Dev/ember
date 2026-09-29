#pragma once

#include <string_view>

namespace Ember {

class Texture {
public:
    Texture() = default;
    explicit Texture(std::string_view relativePath);
    ~Texture();

    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;
    Texture(Texture&& other) noexcept;
    Texture& operator=(Texture&& other) noexcept;

    static Texture loadFromMemory(const unsigned char* data, int width, int height, int channels);

    void bind(unsigned int unit = 0) const;

private:
    unsigned int m_id = 0;
};

} // namespace Ember