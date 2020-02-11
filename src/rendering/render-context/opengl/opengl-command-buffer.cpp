#include "opengl-command-buffer.hpp"

#include "../render-context.hpp"
#include "opengl-render-command.hpp"

namespace DadEngine
{
    OpenGLCommandBuffer::OpenGLCommandBuffer(RenderContext *_renderContext)
        : CommandBuffer(_renderContext)
    {
    }

    void OpenGLCommandBuffer::BeginRecord()
    {
        for (OpenGLRenderCommand *currentRenderCmd : m_commands)
        {
            delete currentRenderCmd;
        }

        m_commands.Clear();
    }

    void OpenGLCommandBuffer::EndRecord()
    {
        m_ptrRenderContext->SubmitCommandBuffer(this);
    }
} // namespace DadEngine
