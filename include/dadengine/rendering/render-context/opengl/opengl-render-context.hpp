#ifndef __OPENGL_RENDER_CONTEXT_HPP_
#define __OPENGL_RENDER_CONTEXT_HPP_

#include "../../../core/core.hpp"
#include "../../window/window.hpp"
#include "opengl-command-buffer.hpp"
#include "opengl.hpp"
#include "render-context.hpp"


namespace DadEngine
{
    class OpenGLRenderContext : public RenderContext
    {

        public:
        OpenGLRenderContext(Window &_window);

        void ClearColorBuffer(Color &_clearColor, CommandBuffer *_commandBuffer) override final;

        void ClearDepthStencilBuffer(float _depthValue,
                                     uint32_t _stencilValue,
                                     CommandBuffer *_commandBuffer) override final;

        void Present(CommandBuffer *_commandBuffer) override final;

        void Draw(VertexBuffer *_vertexBuffer, CommandBuffer *_commandBuffer) override final;

        void DrawMultiples(VertexBuffer *_vertexBuffer,
                           int32_t _instanceCount,
                           CommandBuffer *_commandBuffer) override final;

        void BindVertexBuffer(VertexBuffer *_vertexBuffer,
                              CommandBuffer *_commandBuffer) override final;

        void BindShaderProgram(Shader *_shader, CommandBuffer *_commandBuffer) override final;

        void SetShaderParameter(Shader *_shader,
                                const char *_parameterName,
                                ShaderParameterType _parameterType,
                                void *_param);

        void BeginRenderPass(RenderPass *_renderPass,
                             Framebuffer *_frameBuffer,
                             CommandBuffer *_commandBuffer) override final{};

        void EndRenderPass(CommandBuffer *_commandBuffer) override final{};


        void SetViewport(Viewport &_viewport, CommandBuffer *_commandBuffer) override final;

        void SetCullingMode(CullingMode _cullingMode,
                            CommandBuffer *_commandBuffer) override final;

        void SetFillMode(FillMode _fillMode, CommandBuffer *_commandBuffer) override final;


        Image *GetBackBuffer() override final
        {
            return nullptr;
        }

        Image *GetDepthStencilBuffer() override final
        {
            return nullptr;
        }

        Framebuffer *GetBackFramebuffer() override final
        {
            return nullptr;
        }

        RenderPass *GetRenderPass() override final
        {
            return nullptr;
        }


        void BeginFrame() override final;

        void EndFrame() override final;

        void SubmitCommandBuffer(CommandBuffer *_commandBuffer) override final;


        VertexBuffer *CreateVertexBuffer(uint32_t _vertexCount,
                                         TArray<float> &_data,
                                         TArray<VertexInput> &_vertexLayout,
                                         uint32_t _verticesStride) override final;

        VertexShader *CreateVertexShader(const char *_shaderCode,
                                         size_t _shaderCodeSize,
                                         TArray<VertexInput> &_vertexInputLayout) override final;
        GeometryShader *CreateGeometryShader(const char *_shaderCode,
                                             size_t _shaderCodeSize) override final;
        FragmentShader *CreateFragmentShader(const char *_shaderCode,
                                             size_t _shaderCodeSize) override final;

        Shader *CreateShader(VertexShader *_vertexShader,
                             GeometryShader *_geometryShader,
                             FragmentShader *_fragmentShader,
                             RenderPass *_renderpass) override final;

        CommandBuffer *CreateCommandBuffer() override final;
        virtual RenderPass *CreateRenderPass(TArray<Image *> &_image) override final
        {
            return nullptr;
        }
        virtual Framebuffer *CreateFramebuffer(Extent2D &_framebufferSize,
                                               RenderPass *_renderPass) override final
        {
            return nullptr;
        }

        private:
        TArray<OpenGLCommandBuffer *> m_submittedCommandBuffers;

        HDC m_HDC = nullptr; // Hardware device context one per rendering thread
        HGLRC m_renderContext = nullptr; // Hardware render context
    };
} // namespace DadEngine

#endif //__OPENGL_RENDER_CONTEXT_HPP_
