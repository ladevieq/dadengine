#ifndef __CAMERA_HPP_
#define __CAMERA_HPP_

#include "FramePacket.hpp"
#include "ViewPacket.hpp"
#include "RenderObject.hpp"

#include "../../Math/Math.hpp"

#include "../../Gameplay/IComponent.hpp"

namespace DadEngine::Rendering
{
	class ::DadEngine::Gameplay::Actor;

	enum ProjectionType
	{
		ORTHOGRAPHIC_PROJECTION,
		PERSPECTIVE_RPOJECTION,
		MAX_PROJECTION,
	};


	struct OrthographicCamera
	{

	};

	struct PerspectiveCamera
	{
		float m_Fov = 90.f;
		float m_Near = 0.1f;
		float m_Far = 1000.f;
	};

	class Camera : public ::DadEngine::Gameplay::IComponent
	{

	public:

		Camera();

		Camera(::DadEngine::Gameplay::Actor* _InOwner);


		void ExtractVisibleObjects(TArray<RenderObject*> _InVisibleObjects, FramePacket& _InFramePacket)
		{
			ViewPacket view;

			_InFramePacket.AddViewPacket(view);

			for (RenderObject* currentObject : _InVisibleObjects)
			{
				if (currentObject->m_bVisible == TRUE)
				{
					view.AddRenderObject(currentObject);
				}
			}
		}


		FORCE_INLINE void SetFov(float _InFov)
		{
			m_Fov = _InFov;

			m_Projection.SetIdentity();
			m_Projection.Perpespective(m_Near, m_Far, m_Fov, 16.f / 9.f);
		}

		FORCE_INLINE void SetPlanes(float _InNear, float _InFar)
		{
			m_Near = _InNear;
			m_Far = _InFar;

			m_Projection.SetIdentity();
			m_Projection.Perpespective(m_Near, m_Far, m_Fov, 16.f / 9.f);
		}

		FORCE_INLINE Matrix4x4 GetProjectionMatrix() const { return m_Projection; }


	private:

		Matrix4x4 m_Projection = {};

		float m_Fov = 90.f;
		float m_Near = 0.1f;
		float m_Far = 1000.f;
	};
}

#endif //__CAMERA_HPP_