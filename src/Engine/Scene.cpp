#include "Engine/Scene.hpp"
#include "Engine/Renderer.hpp"

namespace Ember {

Renderable& Scene::add(const Mesh& mesh, const Texture& texture, const Transform& transform)
{
    m_items.push_back(Renderable{&mesh, &texture, transform});
    return m_items.back();
}

void Scene::draw(Renderer& renderer) const
{
    for (const Renderable& item : m_items) {
        if (!item.mesh || !item.texture) {
            continue;
        }
        renderer.draw(*item.mesh, *item.texture, item.transform.matrix());
    }
}

} // namespace Ember
