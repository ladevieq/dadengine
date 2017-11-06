#ifndef __CAMERA_HPP_
#define __CAMERA_HPP_

#include "FramePacket.hpp"
#include "ViewPacket.hpp"
#include "RenderObject.hpp"

namespace DadEngine::Rendering
{
	class Camera
	{

	public:

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
	};
}

#endif //__CAMERA_HPP_