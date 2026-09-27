#include "Engine/Texture.hpp"
#include "Engine/File.hpp"

#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#define STBI_NO_THREAD_LOCALS
#include <stb_image.h>

#include <iostream>
#include <string>
#include <vector>

namespace Ember {

namespace {

void uploadRgb(unsigned int& id, int width, int height, const unsigned char* pixels)
{
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
}

std::vector<unsigned char> makeChecker(int size, int cell)
{
    std::vector<unsigned char> pixels(static_cast<size_t>(size * size * 3));
    for (int y = 0; y < size; ++y) {
        for (int x = 0; x < size; ++x) {
            const bool on = ((x / cell) + (y / cell)) % 2 == 0;
            const size_t i = static_cast<size_t>((y * size + x) * 3);
            if (on) {
                pixels[i + 0] = 220;
                pixels[i + 1] = 70;
                pixels[i + 2] = 50;
            } else {
                pixels[i + 0] = 40;
                pixels[i + 1] = 50;
                pixels[i + 2] = 70;
            }
        }
    }
    return pixels;
}

} // namespace

Texture::Texture(std::string_view relativePath)
{
    const auto path = assetPath(relativePath);
    stbi_set_flip_vertically_on_load(1);

    int width = 0;
    int height = 0;
    int channels = 0;
    unsigned char* pixels = stbi_load(path.string().c_str(), &width, &height, &channels, 3);
    if (pixels) {
        uploadRgb(m_id, width, height, pixels);
        stbi_image_free(pixels);
        return;
    }

    std::cerr << "Texture load failed (" << path.string() << "): "
              << stbi_failure_reason() << " — using built-in checker\n";
    auto fallback = makeChecker(64, 8);
    uploadRgb(m_id, 64, 64, fallback.data());
}

Texture::~Texture()
{
    if (m_id) {
        glDeleteTextures(1, &m_id);
    }
}

Texture::Texture(Texture&& other) noexcept : m_id(other.m_id)
{
    other.m_id = 0;
}

Texture& Texture::operator=(Texture&& other) noexcept
{
    if (this != &other) {
        if (m_id) {
            glDeleteTextures(1, &m_id);
        }
        m_id = other.m_id;
        other.m_id = 0;
    }
    return *this;
}

void Texture::bind(unsigned int unit) const
{
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, m_id);
}

} // namespace Ember
