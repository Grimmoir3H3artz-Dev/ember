#pragma once

#include "Engine/Transform.hpp"
#include <glm/glm.hpp>
#include <vector>

namespace Ember {

class Mesh;
class Texture;
class Renderer;

struct Renderable {
    const Mesh* mesh = nullptr;
    const Texture* texture = nullptr;
    Transform transform;
    glm::vec4 baseColorFactor{1.0f, 1.0f, 1.0f, 1.0f}; // ADDED
};

class Scene {
public:
    Renderable& add(const Mesh& mesh, const Texture& texture, const Transform& transform = {}, 
                     const glm::vec4& baseColorFactor = glm::vec4(1.0f)); // UPDATED
    void draw(Renderer& renderer) const;
    std::vector<Renderable>& items() { return m_items; }

private:
    std::vector<Renderable> m_items;
};

} // namespace Ember