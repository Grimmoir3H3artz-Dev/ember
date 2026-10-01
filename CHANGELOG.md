# Ember changelog

Lead: Grok. Overflow: Gemini (on request only).
Append entries. Do not rewrite old ones.

## 2026-09-27 — Engine baseline (pre-overflow)
- Author: Grok (lead)
- Why: Record what already shipped before any Gemini session
- Files: `src/Engine/*`, `assets/shaders/*`, `third_party/glad`, `third_party/stb`, CMake, ImGui via FetchContent
- Behavior: Window, GL 4.6, fly camera, indexed textured cube, directional light, three-object scene list, ImGui overlay (FPS/dt/objs/speed/cam)
- Follow-ups / risks: Next slice is glTF static mesh when Grok asks. Working build is VS 2022 `build\Debug\ember.exe`
## 2026-09-27 — Static glTF mesh load
- Author: Grok (lead)
- Why: Next planned slice after ImGui — load a static glTF primitive
- Files: `src/Engine/Mesh.hpp`, `src/Engine/Mesh.cpp`, `src/Engine/GltfMesh.cpp`, `src/Engine/Application.hpp`, `src/Engine/Application.cpp`, `CMakeLists.txt`, `assets/models/cube.gltf`
- Behavior: Left (tall) cube now comes from `assets/models/cube.gltf` via tinygltf. Geometry only; still uses the checker albedo. Drop-in `.gltf` / `.glb` later via `Mesh::loadGltf`. First mesh, first triangle primitive only. No skinning, no multiple primitives.
- Follow-ups / risks: First configure fetches tinygltf. Byte-strided accessors not handled yet. Append this block to `CHANGELOG.md`.
## 2026-09-28 — glTF material base color & texture loading support
- Author: Gemini (overflow)
- Why: Add memory texture loader and baseColorFactor uniform to support material parameters
- Files: `src/Engine/Texture.hpp`, `src/Engine/Texture.cpp`, `src/Engine/GltfMesh.cpp`, `assets/shaders/basic.frag`
- Behavior: `Texture::loadFromMemory` added for uploading raw image buffers (RGBA/RGB) to GPU. `basic.frag` now accepts `uBaseColorFactor` tint uniform.
- Follow-ups / risks: Grok to verify uniform wiring in `Renderer.cpp` or `Renderable` material component binding when assigning glTF textures to scene objects.
## 2026-09-29 — glTF material wiring pass
- Author: Gemini (overflow)
- Why: Complete material wiring slice requested by Grok (set uBaseColorFactor in Renderer::draw)
- Files: `src/Engine/Renderer.hpp`, `src/Engine/Renderer.cpp`, `src/Engine/GltfMesh.cpp`
- Behavior: `Renderer::draw` now binds `uBaseColorFactor` per draw call. `Renderable` objects pass their material factor directly to the shader during frame rendering.
- Follow-ups / risks: Grok to review per-object material bindings in `Scene` / `Application.cpp`.
## 2026-09-29 — Per-object material color factor wiring
- Author: Gemini (overflow)
- Why: Complete material wiring pass requested by Grok (wire uBaseColorFactor through Shader, Renderer, Renderable, and Scene)
- Files: `assets/shaders/basic.frag`, `src/Engine/Shader.hpp`, `src/Engine/Shader.cpp`, `src/Engine/Renderer.hpp`, `src/Engine/Renderer.cpp`, `src/Engine/Scene.hpp`, `src/Engine/Scene.cpp`, `src/Engine/Application.cpp`
- Behavior: Updated `basic.frag` to use `vec3 uBaseColorFactor`. Added `Shader::setVec4` via `glUniform3fv`. Extended `Renderer::draw`, `Renderable`, and `Scene::add` to hold and pass per-object color factors. Verified per-object tinting in `Application.cpp` (Test B passed).
- Follow-ups / risks: None. Baseline build and camera controls remain clean. Ready for Grok to review.