#pragma once

#include "Engine/Camera.hpp"
#include "Engine/Mesh.hpp"
#include "Engine/Shader.hpp"
#include "Engine/Texture.hpp"

#include <glm/glm.hpp>

namespace Ember {

class Window;

class Renderer {
public:
    explicit Renderer(Window& window);
    ~Renderer() = default;

    void beginFrame();
    void draw(const Mesh& mesh, const Texture& texture, const glm::mat4& model);
    void endFrame();

    Camera& camera() { return m_camera; }

private:
    Window& m_window;
    Shader m_shader;
    Camera m_camera;
};

} // namespace Ember
