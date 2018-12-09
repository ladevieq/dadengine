#include "Camera.hpp"

#include "../../Gameplay/Gameplay.hpp"

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
}