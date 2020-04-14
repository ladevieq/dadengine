#pragma once

#include "math/matrix/matrix4x4.hpp"
#include "math/vector/vector3.hpp"

namespace DadEngine
{
    class Camera
    {
        public:
        Camera(Vector3 _position, Vector3 _direction, float _aspect);

        float near = 0.1f;
        float far = 1000.f;
        float fov = 60.f;

        Vector3 position;
        Vector3 direction;

        Matrix4x4 view;
        Matrix4x4 projection;
    };
} // namespace DadEngine
