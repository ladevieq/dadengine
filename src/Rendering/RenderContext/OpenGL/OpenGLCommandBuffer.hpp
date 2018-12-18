#ifndef __OPENGL_COMMAND_BUFFER_HPP_
#define __OPENGL_COMMAND_BUFFER_HPP_

#include "../../../Core/Core.hpp"
#include "../../CommandBuffer.hpp"

namespace DadEngine::Rendering
{
    class RenderContext;
    struct OpenGLRenderCommand;

	class OpenGLCommandBuffer : public CommandBuffer
	{

	public:

		OpenGLCommandBuffer(RenderContext *_InRenderContext);

		void BeginRecord() override final;

		void EndRecord() override final;

		TArray<OpenGLRenderCommand*> m_Commands;
	};
}

#endif //!__OPENGL_COMMAND_BUFFER_HPP_