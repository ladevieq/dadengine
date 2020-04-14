#include "model.hpp"

namespace DadEngine
{
    VertexBuffer::VertexBuffer(std::vector<Vertex> &&_vertices)
        : vertices(_vertices)
    {
#if defined(_OPENGL)
        glGenVertexArrays(1, &vertexArrayID);
        glBindVertexArray(vertexArrayID);

        glGenBuffers(1, &vertexBufferID);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);

        glBufferData(GL_ARRAY_BUFFER,
                     static_cast<GLsizei>(vertices.size() * sizeof(Vertex)),
                     vertices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                              reinterpret_cast<void *>(offsetof(Vertex, normal)));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                              reinterpret_cast<void *>(offsetof(Vertex, tangent)));
        glEnableVertexAttribArray(2);

        glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                              reinterpret_cast<void *>(offsetof(Vertex, uv0)));
        glEnableVertexAttribArray(3);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindVertexArray(0);
#elif defined(_VULKAN)
#endif
    }


    IndexBuffer::IndexBuffer(std::vector<uint32_t> &&_indices)
        : indices(_indices)
    {
#if defined(_OPENGL)
        glGenBuffers(1, &elementBufferID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferID);

        glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                     static_cast<GLsizei>(indices.size() * sizeof(uint32_t)),
                     indices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
#elif defined(_VULKAN)
#endif
    }

    Texture::Texture(uint8_t *_data, int32_t _width, int32_t _height, int32_t _channels, Sampler _sampler, bool _hasAlpha)
        : sampler(_sampler), data(_data), width(_width), height(_height),
          channels(_channels), hasAlpha(_hasAlpha)
    {
#if defined(_OPENGL)
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, sampler.wrapS);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, sampler.wrapT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, sampler.minFilter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, sampler.magFilter);

        glTexImage2D(GL_TEXTURE_2D, 0, hasAlpha ? GL_RGBA : GL_RGB, width, height,
                     0, hasAlpha ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);

        glGenerateMipmap(GL_TEXTURE_2D);

        glBindTexture(GL_TEXTURE_2D, 0);
#elif defined(_VULKAN)
#endif
    }


    void Primitive::Render()
    {
#if defined(_OPENGL)
        glBindVertexArray(vertices.vertexArrayID);

        glUniform4fv(0, 1, reinterpret_cast<float *>(&material.baseColorFactor));
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, material.baseColorTexture.textureID);
        glUniform1i(1, 0);

        glUniform1f(3, material.metallicFactor);
        glUniform1f(9, material.roughnessFactor);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, material.metallicRoughnessTexture.textureID);
        glUniform1i(4, 1);

        glUniform1f(6, material.normalScale);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, material.normalTexture.textureID);
        glUniform1i(7, 2);

        // glUniform1f(8, material.occlusionStrength);
        // glActiveTexture(GL_TEXTURE3);
        // glBindTexture(GL_TEXTURE_2D, material.occlusionTexture.textureID);
        // glUniform1i(9, 3);

        // glUniform3f(4, material.emissiveFactor.x, material.emissiveFactor.y,
        // material.emissiveFactor.z); glActiveTexture(GL_TEXTURE4); glBindTexture(GL_TEXTURE_2D,
        // material.emissiveTexture.textureID); glUniform1i(4, 4);

        if (indices.indices.empty())
        {
            glDrawArrays(drawMode, 0, static_cast<GLsizei>(vertices.vertices.size()));
        }
        else
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices.elementBufferID);

            glDrawElements(drawMode, static_cast<GLsizei>(indices.indices.size()),
                           GL_UNSIGNED_INT, nullptr);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }

        glBindVertexArray(0);
#elif defined(_VULKAN)
#endif
    }

    void Mesh::Render()
    {
        for (auto &primitive : m_primitives)
        {
            if (!primitive.material.hasTransparency)
            {
                primitive.Render();
            }
        }

        for (auto &primitive : m_primitives)
        {
            if (primitive.material.hasTransparency)
            {
                primitive.Render();
            }
        }
    }
} // namespace DadEngine
