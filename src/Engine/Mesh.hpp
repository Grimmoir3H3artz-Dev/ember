#pragma once

#include <string_view>
#include <vector>

namespace Ember {

class Mesh {
public:
    static Mesh makeColoredCube();
    static Mesh makeTexturedCube();
    static Mesh fromInterleaved(const std::vector<float>& vertices,
                                const std::vector<unsigned int>& indices);
    static Mesh loadGltf(std::string_view relativePath);

    Mesh() = default;
    ~Mesh();

    Mesh(const Mesh&) = delete;
    Mesh& operator=(const Mesh&) = delete;
    Mesh(Mesh&& other) noexcept;
    Mesh& operator=(Mesh&& other) noexcept;

    void draw() const;

private:
    unsigned int m_vao = 0;
    unsigned int m_vbo = 0;
    unsigned int m_ebo = 0;
    int m_indexCount = 0;
    int m_vertexCount = 0;
};

} // namespace Ember
