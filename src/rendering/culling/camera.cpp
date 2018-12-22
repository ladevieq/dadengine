#include "camera.hpp"

#include "frame-packet.hpp"
#include "view-packet.hpp"
#include "render-object.hpp"
#include "../../gameplay/gameplay.hpp"

namespace DadEngine::Rendering
{
	Camera::Camera()
	{
		m_Projection.Perpespective(m_Near, m_Far, m_Fov);

		CameraManager::GetCameraManager()->AddCamera(this);
	}

	Camera::Camera(Actor* _InOwner)
		: IComponent(_InOwner)
	{
		_InOwner->AddComponent(this);

		m_Projection.Perpespective(m_Near, m_Far, m_Fov);

		CameraManager::GetCameraManager()->AddCamera(this);
	}

	void Camera::ExtractVisibleObjects(TArray<RenderObject *> _InVisibleObjects, FramePacket &_InFramePacket)
    {
        ViewPacket view;

        _InFramePacket.AddViewPacket(view);

        for (RenderObject *currentObject : _InVisibleObjects)
        {
            if (currentObject->m_bVisible == TRUE)
            {
                view.AddRenderObject(currentObject);
            }
        }
    }

	void Camera::SetFov(float _InFov)
    {
        m_Fov = _InFov;

        m_Projection.SetIdentity();
        m_Projection.Perpespective(m_Near, m_Far, m_Fov);
    }

    void Camera::SetPlanes(float _InNear, float _InFar)
    {
        m_Near = _InNear;
        m_Far = _InFar;

        m_Projection.SetIdentity();
        m_Projection.Perpespective(m_Near, m_Far, m_Fov);
    }

    Matrix4x4 Camera::GetProjectionMatrix() const
    {
        return m_Projection;
    }
}