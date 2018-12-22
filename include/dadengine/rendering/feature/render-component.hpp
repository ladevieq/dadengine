#ifndef __RENDER_COMPONENT_HPP_
#define __RENDER_COMPONENT_HPP_

#include "../culling/render-object.hpp"
#include "../culling/frame-packet.hpp"

namespace DadEngine::Rendering
{
	class RenderComponent
	{

	public:

		virtual void Extract(FramePacket& _InFramePacket) = 0;

		RenderObject* m_RenderObjectHandle = nullptr;
	};
}

#endif //__RENDER_COMPONENT_HPP_