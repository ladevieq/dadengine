#ifndef __RENDER_OBJECT_HPP_
#define __RENDER_OBJECT_HPP_

#include <stdint.h>
#include "../../Core/Defines.hpp"

namespace DadEngine::Rendering
{
	class RenderComponent;

	class RenderObject
	{

	public:

		RenderObject(RenderComponent *_InComponent);

		uint8_t m_bVisible = TRUE;

		RenderComponent* m_renderComponentHandle;
	};
}

#endif //__RENDER_OBJECT_HPP_