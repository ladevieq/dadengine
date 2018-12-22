#include "camera-manager.hpp"

namespace DadEngine::Gameplay
{
	CameraManager* s_CameraManager = new CameraManager();


	void CameraManager::AddCamera(Rendering::Camera* _InNewCamera)
	{
		m_Cameras.Add(_InNewCamera);

		m_MainCamera = _InNewCamera;
	}

	CameraManager* CameraManager::GetCameraManager()
	{
		return s_CameraManager;
	}
}