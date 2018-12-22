#ifndef __STATIC_MESH_COMPONENT_HPP_
#define __STATIC_MESH_COMPONENT_HPP_

#include "render-component.hpp"

namespace DadEngine::Rendering
{
	struct StaticMeshData
	{
		
	};

	class StaticMeshComponent : public RenderComponent
	{

	public:

		void Extract(FramePacket& _InFramePacket) override final
		{
			StaticMeshData data;

			_InFramePacket.AddExtractedRenderObjectData(m_RenderObjectHandle, data);
		}
	};
}

#endif //__STATIC_MESH_COMPONENT_HPP_