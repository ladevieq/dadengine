#ifndef __COMMAND_BUFFER_HPP_
#define __COMMAND_BUFFER_HPP_

#include "RenderContext/RenderContext.hpp"
#include "RenderCommand.hpp"
#include "Color.hpp"
#include "../Core/Core.hpp"

namespace DadEngine::Rendering
{
	class CommandBuffer
	{
	public:

		CommandBuffer(RenderContext* _InRenderContext)
			: m_ptrRenderContext(_InRenderContext)
		{}


		virtual void BeginRecord() = 0;

		virtual void EndRecord() = 0;


		// Commands
		void ClearColor(Color _ColorValue) { m_ptrRenderContext->ClearColorBuffer(_ColorValue, this); };

		void ClearDepthStencil(float _DepthValue, uint32_t _InStencilValue) { m_ptrRenderContext->ClearDepthStencilBuffer(_DepthValue, _InStencilValue, this); }

		void Present() { m_ptrRenderContext->Present(this); }

		void BindShader(Shader* _InShader) { m_ptrRenderContext->BindShaderProgram(_InShader, this); }

		void BindVertexBuffer(VertexBuffer* _InVertexBuffer) { m_ptrRenderContext->BindVertexBuffer(_InVertexBuffer, this); }

		void DrawVertexBuffer(VertexBuffer* _InVertexBuffer) { m_ptrRenderContext->Draw(_InVertexBuffer, this); }

		void DrawVertexBufferMultipleTimes(VertexBuffer* _InVertexBuffer, int32_t _InInstanceCount) { m_ptrRenderContext->DrawMultiples(_InVertexBuffer, _InInstanceCount, this); }

		void BeginRenderPass(RenderPass* _InRenderPass, Framebuffer* _InFrameBuffer) { m_ptrRenderContext->BeginRenderPass(_InRenderPass, _InFrameBuffer, this); }

		void EndRenderPass(RenderPass* _InRenderPass) { m_ptrRenderContext->EndRenderPass(this); }


	protected:

		RenderContext* m_ptrRenderContext = nullptr;
	};
}

#endif //__COMMAND_BUFFER_HPP_