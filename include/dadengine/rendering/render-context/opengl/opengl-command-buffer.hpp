#ifndef __OPENGL_COMMAND_BUFFER_HPP_
#define __OPENGL_COMMAND_BUFFER_HPP_

#include "../../../core/core.hpp"
#include "../../command-buffer.hpp"

namespace DadEngine
{
    class RenderContext;
    struct OpenGLRenderCommand;

    class OpenGLCommandBuffer : public CommandBuffer
    {

        public:
        OpenGLCommandBuffer(RenderContext *_renderContext);

        void BeginRecord() override final;

        void EndRecord() override final;

        TArray<OpenGLRenderCommand *> m_commands;
    };
} // namespace DadEngine

#endif //!__OPENGL_COMMAND_BUFFER_HPP_

