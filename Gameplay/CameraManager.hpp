#ifndef __CAMERA_MANAGER_HPP_
#define __CAMERA_MANAGER_HPP_


#include "../Core/Core.hpp"

#include "../Rendering/Culling/Camera.hpp"


namespace DadEngine::Gameplay
{
	class CameraManager
	{

	public:

		CameraManager() = default;

		void AddCamera(Rendering::Camera* _InNewCamera);


		static CameraManager* GetCameraManager();


		FORCE_INLINE Rendering::Camera* GetMainCamera() { return m_MainCamera; }


		TArray<Rendering::Camera*> m_Cameras;

		Rendering::Camera* m_MainCamera = nullptr;
	};
}

#endif //!__CAMERA_MANAGER_HPP_