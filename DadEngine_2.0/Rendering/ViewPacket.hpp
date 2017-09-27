#ifndef __VIEW_PACKET_HPP_
#define __VIEW_PACKET_HPP_

#include "../Core/Core.hpp"
#include "FramePacket.hpp"
#include "RenderObject.hpp"
#include "Feature/RenderComponent.hpp"

namespace DadEngine::Rendering
{
	// One camera rendering informations
	class ViewPacket
	{

	public:

		ViewPacket();

		// Add reference to a visible object for this camera
		void AddRenderObject(RenderObject* _InVisibleObject);

		// Etract all render node information to a frame packe
		void ExtractObjects(FramePacket& _InFramePacket);

		TArray<RenderObject*> m_VisibleObjects; // Enculer de tableau qui s'initialise pas
	};
}

#endif //__VIEW_PACKET_HPP_