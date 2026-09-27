#pragma once

#include "Engine/Mesh.hpp"
#include "Engine/Renderer.hpp"
#include "Engine/Window.hpp"

namespace Ember {

class Application {
public:
    Application();
    int run();

private:
    Window m_window;
    Renderer m_renderer;
    Mesh m_cube;
};

} // namespace Ember
