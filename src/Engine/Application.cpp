#include "Engine/Application.hpp"

#include <GLFW/glfw3.h>
#include <imgui.h>
#include <glm/gtc/matrix_transform.hpp>

#include <algorithm>
#include <chrono>
#include <iostream>

namespace Ember {

Application::Application()
    : m_window(1280, 720, "Ember Engine")
    , m_renderer(m_window)
    , m_albedo("textures/checker.ppm")
    , m_cube(Mesh::makeTexturedCube())
    , m_gltfCube(Mesh::loadGltf("models/cube.gltf"))
    , m_ui(m_window.handle())
{
    m_scene.add(m_cube, m_albedo, Transform{{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}});
    m_scene.add(m_cube, m_albedo, Transform{{2.2f, 0.0f, -0.4f}, {0.0f, 25.0f, 0.0f}, {0.7f, 0.7f, 0.7f}});
    m_scene.add(m_gltfCube, m_albedo, Transform{{-2.0f, 0.35f, 0.6f}, {15.0f, -20.0f, 0.0f}, {0.55f, 1.4f, 0.55f}});
}

int Application::run()
{
    using Clock = std::chrono::steady_clock;
    auto last = Clock::now();

    m_renderer.camera().reset();

    std::cout << "Ember camera\n"
              << "  RMB + mouse  look\n"
              << "  WASD         move\n"
              << "  Space / Ctrl up / down\n"
              << "  Shift        sprint\n"
              << "  Scroll       move speed\n"
              << "  R            reset view\n"
              << "  Esc          quit\n";

    float moveSpeed = 3.5f;

    while (!m_window.shouldClose()) {
        m_window.pollEvents();
        if (m_window.keyDown(GLFW_KEY_ESCAPE)) {
            m_window.requestClose();
        }

        const auto now = Clock::now();
        const float dt = std::clamp(
            std::chrono::duration<float>(now - last).count(), 0.0f, 0.05f);
        last = now;

        Camera& cam = m_renderer.camera();

        const float scroll = m_window.consumeScrollY();
        if (scroll != 0.0f) {
            moveSpeed = std::clamp(moveSpeed * (scroll > 0.0f ? 1.15f : 1.0f / 1.15f), 0.4f, 25.0f);
        }

        if (m_window.keyDown(GLFW_KEY_R)) {
            cam.reset();
        }

        const glm::vec2 look = m_window.consumeCursorDelta();
        constexpr float kLookSensitivity = 0.12f;
        cam.addYawPitch(look.x * kLookSensitivity, -look.y * kLookSensitivity);

        glm::vec3 local{0.0f};
        if (m_window.keyDown(GLFW_KEY_W)) {
            local.z += 1.0f;
        }
        if (m_window.keyDown(GLFW_KEY_S)) {
            local.z -= 1.0f;
        }
        if (m_window.keyDown(GLFW_KEY_D)) {
            local.x += 1.0f;
        }
        if (m_window.keyDown(GLFW_KEY_A)) {
            local.x -= 1.0f;
        }
        if (m_window.keyDown(GLFW_KEY_SPACE)) {
            local.y += 1.0f;
        }
        if (m_window.keyDown(GLFW_KEY_LEFT_CONTROL) || m_window.keyDown(GLFW_KEY_RIGHT_CONTROL)) {
            local.y -= 1.0f;
        }
        if (glm::length(local) > 0.0f) {
            local = glm::normalize(local);
        }
        const float speedMul = m_window.keyDown(GLFW_KEY_LEFT_SHIFT) ? 2.5f : 1.0f;
        cam.moveLocal(local * (moveSpeed * speedMul * dt));
        cam.updateView();

        m_scene.items()[0].transform.rotationDeg.y += 18.0f * dt;

        m_renderer.beginFrame();
        m_scene.draw(m_renderer);

        m_ui.beginFrame();
        ImGui::SetNextWindowPos({16.0f, 16.0f}, ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowSize({280.0f, 180.0f}, ImGuiCond_FirstUseEver);
        ImGui::Begin("Ember");
        ImGui::Text("GPU  AMD Vega 6 path");
        ImGui::Text("FPS  %.0f", ImGui::GetIO().Framerate);
        ImGui::Text("dt   %.2f ms", dt * 1000.0f);
        ImGui::Text("objs %zu", m_scene.items().size());
        ImGui::Text("speed %.1f", moveSpeed);
        const auto& p = cam.position();
        ImGui::Text("cam  %.1f %.1f %.1f", p.x, p.y, p.z);
        ImGui::End();
        m_ui.endFrame();

        m_renderer.endFrame();
    }

    return 0;
}

} // namespace Ember
