#ifndef __RENDER_OBJECT_HPP_
#define __RENDER_OBJECT_HPP_

#include "../../Core/Core.hpp"

namespace DadEngine::Rendering
{
	class RenderComponent;

	class RenderObject
	{

	public:

		RenderObject(RenderComponent* _InComponent)
		{
			m_renderComponentHandle = _InComponent;
		}

		uint8 m_bVisible = TRUE;

		RenderComponent* m_renderComponentHandle;
	};
}

#endif //__RENDER_OBJECT_HPP_