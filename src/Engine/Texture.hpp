#pragma once

#include <string_view>

namespace Ember {

class Texture {
public:
    explicit Texture(std::string_view relativePath);
    ~Texture();

    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;
    Texture(Texture&& other) noexcept;
    Texture& operator=(Texture&& other) noexcept;

    void bind(unsigned int unit = 0) const;
    unsigned int id() const { return m_id; }

private:
    unsigned int m_id = 0;
};

} // namespace Ember
