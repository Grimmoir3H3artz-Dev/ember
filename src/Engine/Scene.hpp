#pragma once

#include "Engine/Transform.hpp"

#include <vector>

namespace Ember {

class Mesh;
class Texture;
class Renderer;

struct Renderable {
    const Mesh* mesh = nullptr;
    const Texture* texture = nullptr;
    Transform transform;
};

class Scene {
public:
    Renderable& add(const Mesh& mesh, const Texture& texture, const Transform& transform = {});
    void draw(Renderer& renderer) const;
    std::vector<Renderable>& items() { return m_items; }

private:
    std::vector<Renderable> m_items;
};

} // namespace Ember
