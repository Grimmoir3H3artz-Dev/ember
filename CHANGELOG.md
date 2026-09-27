# Ember changelog

Lead: Grok. Overflow: Gemini (on request only).
Append entries. Do not rewrite old ones.

## 2026-09-27 — Engine baseline (pre-overflow)
- Author: Grok (lead)
- Why: Record what already shipped before any Gemini session
- Files: `src/Engine/*`, `assets/shaders/*`, `third_party/glad`, `third_party/stb`, CMake, ImGui via FetchContent
- Behavior: Window, GL 4.6, fly camera, indexed textured cube, directional light, three-object scene list, ImGui overlay (FPS/dt/objs/speed/cam)
- Follow-ups / risks: Next slice is glTF static mesh when Grok asks. Working build is VS 2022 `build\Debug\ember.exe`
