#include "camera.hpp"

#include "../math/matrix/matrix4x4.hpp"

namespace DadEngine
{
    Camera::Camera()
    {
        m_projection.Perpespective(m_near, m_far, m_fov);
    }


    void Camera::SetFov(float _fov)
    {
        m_fov = _fov;

        m_projection.SetIdentity();
        m_projection.Perpespective(m_near, m_far, m_fov);
    }

    void Camera::SetPlanes(float _near, float _far)
    {
        m_near = _near;
        m_far = _far;

        m_projection.SetIdentity();
        m_projection.Perpespective(m_near, m_far, m_fov);
    }

    Matrix4x4 Camera::GetProjectionMatrix() const
    {
        return m_projection;
    }
} // namespace DadEngine
