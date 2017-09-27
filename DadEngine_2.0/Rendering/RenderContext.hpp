#ifndef __RENDER_CONTEXT_HPP_
#define __RENDER_CONTEXT_HPP_

#include "Color.hpp"

namespace DadEngine::Rendering
{
	class RenderContext
	{
	public:

		virtual void ClearBuffer(Color& _InClearColor) = 0;
		virtual void Present() = 0;
	};
}

#endif //__RENDER_CONTEXT_HPP_