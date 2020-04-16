#include "gltf-loader.hpp"

#include <cstdint>

#include <fstream>
#include <ios>
#include <iostream>
#include <vector>

#include <nlohmann/json.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "helpers/file.hpp"
#include "model/model.hpp"
#include "vector/vector3.hpp"

using json = nlohmann::json;

namespace DadEngine
{
    struct PrimitiveAttribute
    {
        uint8_t *data;
        size_t count;
    };

    inline PrimitiveAttribute
    GetPrimitiveAttribute(std::vector<std::vector<uint8_t>> &_buffers, json _gltf, uint32_t _attributeAccesorIndex)
    {
        json accessor            = _gltf["accessors"][_attributeAccesorIndex];
        uint32_t bufferViewIndex = accessor["bufferView"];
        json bufferView          = _gltf["bufferViews"][bufferViewIndex];
        uint32_t bufferIndex     = bufferView["buffer"];
        size_t bufferOffset      = bufferView["byteOffset"];

        return PrimitiveAttribute { &_buffers[bufferIndex][bufferOffset], accessor["count"] };
    }

    inline Texture
    GetTexture(std::filesystem::path _rootPath, const json &_materialTexture, json _gltf)
    {
        uint32_t textureIndex = _materialTexture["index"];
        auto texture          = _gltf["textures"][textureIndex];
        uint32_t samplerIndex = texture["sampler"];
        auto gltfSampler      = _gltf["samplers"][samplerIndex];
        uint32_t imageIndex   = texture["source"];

        // Todo support bufferView images
        std::string imageFilename = _gltf["images"][imageIndex]["uri"];
        auto imagePath            = _rootPath.append(imageFilename);
        auto imageExtension       = imagePath.extension();
        bool hasAlpha             = imageExtension.string() == ".png";

#if defined(OPENGL)
        Sampler sampler { gltfSampler["magFilter"], gltfSampler["minFilter"],
                          gltfSampler["wrapS"], gltfSampler["wrapT"] };
#elif defined(VULKAN)
        Sampler sampler;
#endif

        int32_t width;
        int32_t height;
        int32_t channels;
        uint8_t *imageData
            = stbi_load(imagePath.string().c_str(), &width, &height, &channels, 0);

        if (!imageData) {
            std::cout << "Failed to load image : " << imagePath.string() << "\n";
        }

        return { imageData, width, height, channels, sampler, hasAlpha };
    }

    std::vector<DadEngine::Mesh> LoadGLTF(std::filesystem::path &_path)
    {
        json gltf;

        std::fstream(_path.string()) >> gltf;

        // Store buffers content
        std::vector<std::vector<uint8_t>> buffers;
        for (const auto &buffer : gltf["buffers"]) {
            auto filename = buffer["uri"].get<std::string>();
            auto pathCopy = _path;
            auto filepath = pathCopy.replace_filename(filename);

            auto rawBuffer = ReadFile(filepath);

            buffers.push_back(rawBuffer);
        }

        // Loop through meshes
        std::vector<DadEngine::Mesh> meshes;
        for (const auto &gltfMesh : gltf["meshes"]) {
            DadEngine::Mesh mesh;

            for (const auto &primitive : gltfMesh["primitives"]) {
                uint32_t indicesAccessorIndex = primitive["indices"];
                auto indicesAccessor = gltf["accessors"][indicesAccessorIndex];
                size_t indicesCount  = indicesAccessor["count"];
                uint32_t bufferViewIndex = indicesAccessor["bufferView"];
                auto indicesBufferView   = gltf["bufferViews"][bufferViewIndex];
                uint32_t indexBufferIndex  = indicesBufferView["buffer"];
                uint32_t indexBufferOffset = indicesBufferView["byteOffset"];
                uint8_t *rawIndices = &buffers[indexBufferIndex][indexBufferOffset];

                std::vector<uint32_t> indicesBuffer(indicesCount);
                if (indicesAccessor["componentType"] == 5123) { // 2 byte indices
                    const uint16_t *indices = reinterpret_cast<uint16_t *>(rawIndices);

                    for (size_t k = 0; k < indicesCount; k++) {
                        indicesBuffer[k] = static_cast<uint32_t>(indices[k]);
                    }
                }
                else {
                    const uint32_t *indices = reinterpret_cast<uint32_t *>(rawIndices);
                    indicesBuffer.assign(indices, indices + indicesCount * sizeof(uint32_t));
                }


                const auto attributes = primitive["attributes"];
                std::vector<DadEngine::Vertex> vertexBuffer;

                if (attributes.count("POSITION")) {
                    auto positionAttribute
                        = GetPrimitiveAttribute(buffers, gltf, attributes["POSITION"]);
                    const DadEngine::Vector3 *positionsArray
                        = reinterpret_cast<DadEngine::Vector3 *>(
                            positionAttribute.data);

                    for (size_t i = 0; i < positionAttribute.count; i++) {
                        DadEngine::Vertex vertex;

                        vertex.position = positionsArray[i];

                        vertexBuffer.push_back(vertex);
                    }
                }

                if (attributes.count("NORMAL")) {
                    auto normalAttribute
                        = GetPrimitiveAttribute(buffers, gltf, attributes["NORMAL"]);
                    const DadEngine::Vector3 *normalsArray
                        = reinterpret_cast<DadEngine::Vector3 *>(normalAttribute.data);

                    for (size_t i = 0; i < normalAttribute.count; i++) {
                        vertexBuffer[i].normal = normalsArray[i];
                    }
                }

                if (attributes.count("TANGENT")) {
                    auto tangentAttribute
                        = GetPrimitiveAttribute(buffers, gltf, attributes["TANGENT"]);
                    const DadEngine::Vector4 *tangentArray
                        = reinterpret_cast<DadEngine::Vector4 *>(
                            tangentAttribute.data);

                    for (size_t i = 0; i < tangentAttribute.count; i++) {
                        vertexBuffer[i].tangent = tangentArray[i];
                    }
                }

                if (attributes.count("TEXCOORD_0")) {
                    auto texCoord0Attribute
                        = GetPrimitiveAttribute(buffers, gltf, attributes["TEXCOORD_0"]);
                    const Vector2 *texCoord0Array
                        = reinterpret_cast<Vector2 *>(texCoord0Attribute.data);

                    for (size_t i = 0; i < texCoord0Attribute.count; i++) {
                        vertexBuffer[i].uv0 = texCoord0Array[i];
                    }
                }

                VertexBuffer vb(std::move(vertexBuffer));
                IndexBuffer ib(std::move(indicesBuffer));

                uint32_t materialIndex = primitive["material"];
                json gltfMaterial      = gltf["materials"][materialIndex];
                json gltfPBRMaterial   = gltfMaterial["pbrMetallicRoughness"];
                PBRMaterial material;

                if (gltfPBRMaterial.count("baseColorFactor")) {
                    auto baseColorFactor
                        = gltfPBRMaterial["baseColorFactor"].get<std::vector<float>>();
                    material.baseColorFactor = *reinterpret_cast<DadEngine::Vector4 *>(
                        baseColorFactor.data());
                }

                if (gltfPBRMaterial.count("baseColorTexture")) {
                    material.baseColorTexture
                        = GetTexture(_path.parent_path(),
                                     gltfPBRMaterial["baseColorTexture"], gltf);
                }

                if (gltfPBRMaterial.count("metallicFactor")) {
                    auto metallicFactor     = gltfPBRMaterial["metallicFactor"];
                    material.metallicFactor = metallicFactor;
                }

                if (gltfPBRMaterial.count("roughnessFactor")) {
                    auto roughnessFactor = gltfPBRMaterial["roughnessFactor"];
                    material.roughnessFactor = roughnessFactor;
                }

                if (gltfPBRMaterial.count("metallicRoughnessTexture")) {
                    material.metallicRoughnessTexture
                        = GetTexture(_path.parent_path(), gltfPBRMaterial["metallicRoughnessTexture"],
                                     gltf);
                }

                if (gltfMaterial.count("normalTexture")) {
                    material.normalTexture
                        = GetTexture(_path.parent_path(),
                                     gltfMaterial["normalTexture"], gltf);
                }

                if (gltfMaterial.count("occlusionTexture")) {
                    material.occlusionTexture
                        = GetTexture(_path.parent_path(),
                                     gltfMaterial["occlusionTexture"], gltf);
                }

                if (gltfMaterial.count("emissiveFactor")) {
                    auto emissiveFactor
                        = gltfMaterial["emissiveFactor"].get<std::vector<float>>();
                    material.emissiveFactor
                        = *reinterpret_cast<DadEngine::Vector3 *>(emissiveFactor.data());
                }

                if (gltfMaterial.count("emissiveTexture")) {
                    material.emissiveTexture
                        = GetTexture(_path.parent_path(),
                                     gltfMaterial["emissiveTexture"], gltf);
                }

                material.hasTransparency = material.baseColorTexture.hasAlpha;

                mesh.m_primitives.emplace_back(
                    Primitive(std::move(vb), std::move(ib), primitive["mode"], material));
            }

            meshes.push_back(mesh);
        }

        return meshes;
    }
} // namespace DadEngine
