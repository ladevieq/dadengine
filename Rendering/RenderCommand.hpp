#ifndef __RENDER_COMMAND_HPP_
#define __RENDER_COMMAND_HPP_


namespace DadEngine::Rendering
{
	struct RenderCommand
	{
		virtual void Execute(RenderContext* _InRenderContext) = 0;
	};
}

#endif //__RENDER_COMMAND_HPP_