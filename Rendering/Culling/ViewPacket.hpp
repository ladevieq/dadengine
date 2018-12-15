#ifndef __VIEW_PACKET_HPP_
#define __VIEW_PACKET_HPP_

#include "../../Core/Core.hpp"
// #include "../Feature/RenderComponent.hpp"

namespace DadEngine::Rendering
{
    class FramePacket;
    class RenderObject;

	// One camera rendering informations
	class ViewPacket
	{

	public:

		ViewPacket();

		// Add reference to a visible object for this camera
		void AddRenderObject(RenderObject* _InVisibleObject);

		// Etract all render node information to a frame packe
		void ExtractObjects(FramePacket& _InFramePacket);

		TArray<RenderObject*> m_VisibleObjects; // Le tableau ne s'initialise pas
	};
}

#endif //__VIEW_PACKET_HPP_