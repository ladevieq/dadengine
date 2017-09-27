#ifndef __RENDER_COMPONENT_HPP_
#define __RENDER_COMPONENT_HPP_

#include "../RenderObject.hpp"
#include "../FramePacket.hpp"

namespace DadEngine::Rendering
{
	class RenderComponent
	{

	public:

		virtual void Extract(FramePacket& _InFramePacket) = 0;

		RenderObject* m_RenderObjectHandle;
	};
}

#endif //__RENDER_COMPONENT_HPP_