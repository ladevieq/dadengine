#include "command-buffer.hpp"

#include "color.hpp"
#include "render-context/render-context.hpp"

namespace DadEngine
{
    CommandBuffer::CommandBuffer(RenderContext *_renderContext)
        : m_ptrRenderContext(_renderContext)
    {
    }

    void CommandBuffer::ClearColor(Color _colorValue)
    {
        m_ptrRenderContext->ClearColorBuffer(_colorValue, this);
    };

    void CommandBuffer::ClearDepthStencil(float _depthValue, uint32_t _stencilValue)
    {
        m_ptrRenderContext->ClearDepthStencilBuffer(_depthValue, _stencilValue, this);
    }

    void CommandBuffer::Present()
    {
        m_ptrRenderContext->Present(this);
    }

    void CommandBuffer::BindShader(Shader *_shader)
    {
        m_ptrRenderContext->BindShaderProgram(_shader, this);
    }

    void CommandBuffer::BindVertexBuffer(VertexBuffer *_vertexBuffer)
    {
        m_ptrRenderContext->BindVertexBuffer(_vertexBuffer, this);
    }

    void CommandBuffer::DrawVertexBuffer(VertexBuffer *_vertexBuffer)
    {
        m_ptrRenderContext->Draw(_vertexBuffer, this);
    }

    void CommandBuffer::DrawVertexBufferMultipleTimes(VertexBuffer *_vertexBuffer,
                                                      int32_t _instanceCount)
    {
        m_ptrRenderContext->DrawMultiples(_vertexBuffer, _instanceCount, this);
    }

    void CommandBuffer::BeginRenderPass(RenderPass *_renderPass, Framebuffer *_frameBuffer)
    {
        m_ptrRenderContext->BeginRenderPass(_renderPass, _frameBuffer, this);
    }

    void CommandBuffer::EndRenderPass(RenderPass *_renderPass)
    {
        m_ptrRenderContext->EndRenderPass(this);
    }
} // namespace DadEngine
