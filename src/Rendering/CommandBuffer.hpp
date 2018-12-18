#ifndef __COMMAND_BUFFER_HPP_
#define __COMMAND_BUFFER_HPP_

#include <stdint.h>

namespace DadEngine::Rendering
{
    struct Color;
    class VertexBuffer;
    class RenderContext;
	class Shader;
    class RenderPass;
    class Framebuffer;

    class CommandBuffer
    {
        public:
        CommandBuffer(RenderContext *_InRenderContext);


        virtual void BeginRecord() = 0;

        virtual void EndRecord() = 0;


        // Commands
        void ClearColor(Color _ColorValue);

        void ClearDepthStencil(float _DepthValue, uint32_t _InStencilValue);

        void Present();

        void BindShader(Shader *_InShader);

        void BindVertexBuffer(VertexBuffer *_InVertexBuffer);

        void DrawVertexBuffer(VertexBuffer *_InVertexBuffer);

        void DrawVertexBufferMultipleTimes(VertexBuffer *_InVertexBuffer, int32_t _InInstanceCount);

        void BeginRenderPass(RenderPass *_InRenderPass, Framebuffer *_InFrameBuffer);

        void EndRenderPass(RenderPass *_InRenderPass);


        protected:
        RenderContext *m_ptrRenderContext = nullptr;
    };
} // namespace DadEngine::Rendering

#endif //__COMMAND_BUFFER_HPP_