# Ember Engine

Small C++20 game engine starter aimed at modest laptops (AMD Vega 6 / similar iGPUs).

**Now:** window, OpenGL 4.6 core, shader load, perspective camera, rotating colored cube.  
**Not yet:** textures, lighting, glTF, physics, ECS, audio, editor.

## Why this stack

| Choice | Reason |
|---|---|
| C++20 | Engine-owned memory and no GC hitch on a 15W APU |
| OpenGL 4.6 core | Vega 6 supports it; far less boilerplate than Vulkan for v0 |
| GLFW + tiny GL loader + GLM | Window/input, functions, math. Nothing else |
| Forward colored mesh | One draw call. Easy to profile on 6 CUs / 4 GB UMA |

Vulkan is supported by the GPU. Add it later behind a `Renderer` interface once the scene graph and assets exist.

## Layout

```
ember/
  assets/shaders/     GLSL 460
  src/Engine/         Window, Renderer, Shader, Mesh, Camera, Application
  third_party/glad/   Minimal GL 4.6 loader (expand when you need more entry points)
  CMakeLists.txt
  CMakePresets.json
  .vscode/            tasks + launch for VS Code
```

## Prerequisites

**Both platforms**

- CMake 3.24+
- Git (FetchContent pulls GLFW 3.4 and GLM 1.0.1 on first configure)
- A GPU driver that exposes OpenGL 4.6 core

**Linux**

```bash
sudo apt install build-essential ninja-build cmake git \
    libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev libgl1-mesa-dev
```

**Windows**

- Visual Studio 2022 Build Tools (MSVC) or LLVM clang-cl
- [Ninja](https://ninja-build.org/) on PATH
- Recent AMD Adrenalin driver

VS Code extensions: C/C++, CMake Tools (listed in `.vscode/extensions.json`).

## Build

```bash
# Linux
cmake --preset linux-gcc-debug
cmake --build --preset linux-gcc-debug
./build/linux-gcc-debug/ember

# Windows (from "x64 Native Tools" or a shell where cl.exe works)
cmake --preset windows-msvc-debug
cmake --build --preset windows-msvc-debug
.\build\windows-msvc-debug\ember.exe
```

In VS Code: **Terminal → Run Build Task** then **Run Ember**, or F5.

First configure downloads GLFW and GLM. Later configures are offline.

## Controls

- **Esc** — quit
- Cube auto-rotates so you can confirm depth + face colors

## Hardware notes (Vega 6 / 4 GB UMA)

- Stay at 1280×720 or 1920×1080. Do not start with 4K framebuffers.
- Batch later. One material / one VAO per draw is the rule of thumb.
- Dual-channel only covers the first 8 GB of RAM, and 4 GB of that is UMA. Keep CPU working set modest.
- Next cheap wins: indexed meshes, frustum cull, texture atlas, then Blinn-Phong (one directional light).

## Suggested next commits

1. Orbit camera (mouse + WASD)
2. Index buffer + `stb_image` textured cube
3. Directional light in the fragment shader
4. Tiny scene list (`Transform` + `Mesh*` + `Shader*`)
5. ImGui overlay (frame time, draw calls)
6. glTF static mesh via tinygltf
7. Abstract `IRenderer` if you still want Vulkan

Skip ECS until you have more than one kind of object and a reason to query them.

## License

MIT. GLFW and GLM keep their own licenses after FetchContent.
