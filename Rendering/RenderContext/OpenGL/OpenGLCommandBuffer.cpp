#include "OpenGLCommandBuffer.hpp"

#include "../RenderContext.hpp"
#include "OpenGLRenderCommand.hpp"

namespace DadEngine::Rendering
{
    OpenGLCommandBuffer::OpenGLCommandBuffer(RenderContext *_InRenderContext)
        : CommandBuffer(_InRenderContext)
    {
    }

    void OpenGLCommandBuffer::BeginRecord()
    {
        for (OpenGLRenderCommand *currentRenderCmd : m_Commands)
        {
            delete currentRenderCmd;
        }

        m_Commands.Clear();
    }

    void OpenGLCommandBuffer::EndRecord()
    {
        m_ptrRenderContext->SubmitCommandBuffer(this);
    }
}