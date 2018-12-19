#include "CommandBuffer.hpp"

#include "RenderContext/RenderContext.hpp"
#include "Color.hpp"

namespace DadEngine::Rendering
{
    CommandBuffer::CommandBuffer(RenderContext *_InRenderContext)
        : m_ptrRenderContext(_InRenderContext)
    {
    }

    void CommandBuffer::ClearColor(Color _ColorValue)
    {
        m_ptrRenderContext->ClearColorBuffer(_ColorValue, this);
    };

	void CommandBuffer::ClearDepthStencil(float _DepthValue, uint32_t _InStencilValue)
    {
        m_ptrRenderContext->ClearDepthStencilBuffer(_DepthValue, _InStencilValue, this);
    }

    void CommandBuffer::Present()
    {
        m_ptrRenderContext->Present(this);
    }

    void CommandBuffer::BindShader(Shader *_InShader)
    {
        m_ptrRenderContext->BindShaderProgram(_InShader, this);
    }

    void CommandBuffer::BindVertexBuffer(VertexBuffer *_InVertexBuffer)
    {
        m_ptrRenderContext->BindVertexBuffer(_InVertexBuffer, this);
    }

    void CommandBuffer::DrawVertexBuffer(VertexBuffer *_InVertexBuffer)
    {
        m_ptrRenderContext->Draw(_InVertexBuffer, this);
    }

    void CommandBuffer::DrawVertexBufferMultipleTimes(VertexBuffer *_InVertexBuffer, int32_t _InInstanceCount)
    {
        m_ptrRenderContext->DrawMultiples(_InVertexBuffer, _InInstanceCount, this);
    }

    void CommandBuffer::BeginRenderPass(RenderPass *_InRenderPass, Framebuffer *_InFrameBuffer)
    {
        m_ptrRenderContext->BeginRenderPass(_InRenderPass, _InFrameBuffer, this);
    }

    void CommandBuffer::EndRenderPass(RenderPass *_InRenderPass)
    {
        m_ptrRenderContext->EndRenderPass(this);
    }
} // namespace DadEngine::Rendering