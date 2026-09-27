#pragma once

#include "Engine/Mesh.hpp"
#include "Engine/Renderer.hpp"
#include "Engine/Scene.hpp"
#include "Engine/Texture.hpp"
#include "Engine/Ui.hpp"
#include "Engine/Window.hpp"

namespace Ember {

class Application {
public:
    Application();
    int run();

private:
    Window m_window;
    Renderer m_renderer;
    Texture m_albedo;
    Mesh m_cube;
    Mesh m_gltfCube;
    Scene m_scene;
    Ui m_ui;
};

} // namespace Ember
