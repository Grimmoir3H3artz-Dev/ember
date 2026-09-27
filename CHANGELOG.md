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
