#ifndef __COMMAND_BUFFER_HPP_
#define __COMMAND_BUFFER_HPP_

#include <cstdint>

namespace DadEngine
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
        CommandBuffer(RenderContext *_renderContext);


        virtual void BeginRecord() = 0;

        virtual void EndRecord() = 0;


        // Commands
        void ClearColor(Color _colorValue);

        void ClearDepthStencil(float _depthValue, uint32_t _stencilValue);

        void Present();

        void BindShader(Shader *_shader);

        void BindVertexBuffer(VertexBuffer *_vertexBuffer);

        void DrawVertexBuffer(VertexBuffer *_vertexBuffer);

        void DrawVertexBufferMultipleTimes(VertexBuffer *_vertexBuffer, int32_t _instanceCount);

        void BeginRenderPass(RenderPass *_renderPass, Framebuffer *_frameBuffer);

        void EndRenderPass(RenderPass *_renderPass);


        protected:
        RenderContext *m_ptrRenderContext = nullptr;
    };
} // namespace DadEngine

#endif //__COMMAND_BUFFER_HPP_

