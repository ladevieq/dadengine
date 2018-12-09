#ifndef __OPENGL_COMMAND_BUFFER_HPP_
#define __OPENGL_COMMAND_BUFFER_HPP_

#include "../../CommandBuffer.hpp"

namespace DadEngine::Rendering
{
	class OpenGLCommandBuffer : public CommandBuffer
	{

	public:

		OpenGLCommandBuffer(RenderContext* _InRenderContext)
			: CommandBuffer(_InRenderContext)
		{}

		void BeginRecord() override final
		{
			for (OpenGLRenderCommand* currentRenderCmd : m_Commands)
			{
				delete currentRenderCmd;
			}

			m_Commands.Clear();
		}

		void EndRecord() override final { m_ptrRenderContext->SubmitCommandBuffer(this); }

		TArray<OpenGLRenderCommand*> m_Commands;
	};
}

#endif //!__OPENGL_COMMAND_BUFFER_HPP_