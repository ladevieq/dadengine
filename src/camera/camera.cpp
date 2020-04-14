#include "camera.hpp"

namespace DadEngine
{
    Camera::Camera(Vector3 _position, Vector3 _direction, float _aspect)
        : position(_position), direction(_direction)
    {
        Vector3 target = direction - position;
        Vector3 up(0.f, 1.f, 0.f);
        view.LookAtRH(position, target, up);

        projection.PerspectiveRH_NO(near, far, fov, _aspect);
    }
} // namespace DadEngine
