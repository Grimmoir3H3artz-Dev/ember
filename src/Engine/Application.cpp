#include "Engine/Application.hpp"

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include <chrono>
#include <iostream>

namespace Ember {

Application::Application()
    : m_window(1280, 720, "Ember Engine")
    , m_renderer(m_window)
    , m_cube(Mesh::makeColoredCube())
{
}

int Application::run()
{
    using Clock = std::chrono::steady_clock;
    const auto start = Clock::now();

    m_renderer.camera().lookAt({2.4f, 1.6f, 2.8f}, {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f});

    std::cout << "Ember running. ESC quits. WASD unused until camera control lands.\n";

    while (!m_window.shouldClose()) {
        m_window.pollEvents();
        if (m_window.keyDown(GLFW_KEY_ESCAPE)) {
            m_window.requestClose();
        }

        const float t = std::chrono::duration<float>(Clock::now() - start).count();
        glm::mat4 model{1.0f};
        model = glm::rotate(model, t * 0.7f, glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, t * 0.35f, glm::vec3(1.0f, 0.0f, 0.0f));

        m_renderer.beginFrame();
        m_renderer.draw(m_cube, model);
        m_renderer.endFrame();
    }

    return 0;
}

} // namespace Ember
