#include "Engine/Mesh.hpp"
#include "Engine/Texture.hpp"
#include "Engine/File.hpp"

#define TINYGLTF_IMPLEMENTATION
#define TINYGLTF_NO_STB_IMAGE
#define TINYGLTF_NO_STB_IMAGE_WRITE
#define TINYGLTF_NO_EXTERNAL_IMAGE
#include <tiny_gltf.h>

#include <stdexcept>
#include <string>

namespace Ember {
namespace {

template <typename T>
const T* accessorData(const tinygltf::Model& model, const tinygltf::Accessor& accessor)
{
    const tinygltf::BufferView& view = model.bufferViews[static_cast<size_t>(accessor.bufferView)];
    const tinygltf::Buffer& buffer = model.buffers[static_cast<size_t>(view.buffer)];
    return reinterpret_cast<const T*>(buffer.data.data() + view.byteOffset + accessor.byteOffset);
}

} // namespace

Mesh Mesh::loadGltf(std::string_view relativePath)
{
    const auto path = assetPath(relativePath);
    tinygltf::Model model;
    tinygltf::TinyGLTF loader;
    std::string err;
    std::string warn;

    const std::string pathStr = path.string();
    bool ok = false;
    if (pathStr.size() >= 4 && pathStr.substr(pathStr.size() - 4) == ".glb") {
        ok = loader.LoadBinaryFromFile(&model, &err, &warn, pathStr);
    } else {
        ok = loader.LoadASCIIFromFile(&model, &err, &warn, pathStr);
    }
    if (!ok) {
        throw std::runtime_error("glTF load failed (" + pathStr + "): " + err);
    }

    if (model.meshes.empty() || model.meshes[0].primitives.empty()) {
        throw std::runtime_error("glTF has no mesh primitives: " + pathStr);
    }

    const tinygltf::Primitive& prim = model.meshes[0].primitives[0];
    if (prim.mode != TINYGLTF_MODE_TRIANGLES && prim.mode != -1) {
        throw std::runtime_error("glTF primitive is not triangles: " + pathStr);
    }

    auto findAttr = [&](const char* name) -> const tinygltf::Accessor* {
        const auto it = prim.attributes.find(name);
        if (it == prim.attributes.end()) {
            return nullptr;
        }
        return &model.accessors[static_cast<size_t>(it->second)];
    };

    const tinygltf::Accessor* pos = findAttr("POSITION");
    if (!pos) {
        throw std::runtime_error("glTF missing POSITION: " + pathStr);
    }
    const tinygltf::Accessor* nrm = findAttr("NORMAL");
    const tinygltf::Accessor* uv = findAttr("TEXCOORD_0");

    const float* posData = accessorData<float>(model, *pos);
    const float* nrmData = nrm ? accessorData<float>(model, *nrm) : nullptr;
    const float* uvData = uv ? accessorData<float>(model, *uv) : nullptr;

    std::vector<float> vertices;
    vertices.reserve(static_cast<size_t>(pos->count) * 8);
    for (int i = 0; i < pos->count; ++i) {
        vertices.push_back(posData[i * 3 + 0]);
        vertices.push_back(posData[i * 3 + 1]);
        vertices.push_back(posData[i * 3 + 2]);
        if (nrmData) {
            vertices.push_back(nrmData[i * 3 + 0]);
            vertices.push_back(nrmData[i * 3 + 1]);
            vertices.push_back(nrmData[i * 3 + 2]);
        } else {
            vertices.insert(vertices.end(), {0.0f, 1.0f, 0.0f});
        }
        if (uvData) {
            vertices.push_back(uvData[i * 2 + 0]);
            vertices.push_back(uvData[i * 2 + 1]);
        } else {
            vertices.insert(vertices.end(), {0.0f, 0.0f});
        }
    }

    std::vector<unsigned int> indices;
    if (prim.indices >= 0) {
        const tinygltf::Accessor& ia = model.accessors[static_cast<size_t>(prim.indices)];
        indices.resize(static_cast<size_t>(ia.count));
        if (ia.componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT) {
            const auto* src = accessorData<unsigned short>(model, ia);
            for (int i = 0; i < ia.count; ++i) {
                indices[static_cast<size_t>(i)] = src[i];
            }
        } else if (ia.componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT) {
            const auto* src = accessorData<unsigned int>(model, ia);
            for (int i = 0; i < ia.count; ++i) {
                indices[static_cast<size_t>(i)] = src[i];
            }
        } else if (ia.componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE) {
            const auto* src = accessorData<unsigned char>(model, ia);
            for (int i = 0; i < ia.count; ++i) {
                indices[static_cast<size_t>(i)] = src[i];
            }
        } else {
            throw std::runtime_error("Unsupported glTF index type: " + pathStr);
        }
    } else {
        indices.resize(static_cast<size_t>(pos->count));
        for (unsigned int i = 0; i < indices.size(); ++i) {
            indices[i] = i;
        }
    }

    return fromInterleaved(vertices, indices);
}

} // namespace Ember