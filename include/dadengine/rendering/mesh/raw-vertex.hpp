#ifndef __RAW_VERTEX_HPP_
#define __RAW_VERTEX_HPP_

#include "../../math/vector/vector3.hpp"

namespace DadEngine
{
    // All information about one vertex from concrete files(.obj, .fbx, .gltf2.0)
    struct RawVertex
    {
        RawVertex() = default;

        RawVertex(const Vector3 &_position) : position(_position)
        {
        }

        RawVertex(const Vector3 &_position, const Vector3 &_color0)
            : position(_position), color0(_color0)
        {
        }


        Vector3 position = Vector3::Zero();

        Vector3 color0 = Vector3::Zero();
        // Vector3f Color1 = NullVector3f;
        // Vector3f Color2 = NullVector3f;
        // Vector3f Color3 = NullVector3f;

        // Vector3f Normal = NullVector3f;
        // Vector3f Tangent = NullVector3f;
    };
} // namespace DadEngine

#endif // __RAW_VERTEX_HPP_
