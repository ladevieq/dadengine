#ifndef __OPENGL_RENDER_COMMAND_HPP_
#define __OPENGL_RENDER_COMMAND_HPP_

#include <stdint.h>
#include "../../Color.hpp"


namespace DadEngine::Rendering
{
    class Shader;
    class OpenGLShader;
    class VertexBuffer;
    class OpenGLCommandBuffer;


    struct OpenGLRenderCommand
    {
        virtual void Execute() = 0;
    };


    struct OpenGLCommandClearColorBuffer : public OpenGLRenderCommand
    {
        Color m_ClearColor = {};

        OpenGLCommandClearColorBuffer(Color &_InClearColorValue);

        void Execute() override final;
    };

    struct OpenGLCommandClearDepthStencilBuffer : public OpenGLRenderCommand
    {
        double m_ClearDepthValue = 0.0;
        uint32_t m_ClearStencilValue = 0U;

        OpenGLCommandClearDepthStencilBuffer(double _InClearDepthValue, uint32_t _InClearStencilValue);


        void Execute() override final;
    };

    struct OpenGLCommandDraw : public OpenGLRenderCommand
    {
        VertexBuffer *m_VertexBuffer = nullptr;

        OpenGLCommandDraw(VertexBuffer *_InVertexBuffer);

        void Execute() override final;
    };

    struct OpenGLCommandDrawMultiples : public OpenGLRenderCommand
    {
        VertexBuffer *m_VertexBuffer = nullptr;
        int32_t m_InstanceCount = 0;

        OpenGLCommandDrawMultiples(VertexBuffer *_InVertexBuffer, int32_t _InInstanceCount);

        void Execute() override final;
    };

    struct OpenGLBindVertexBuffer : public OpenGLRenderCommand
    {
        VertexBuffer *m_VertexBuffer = nullptr;

        OpenGLBindVertexBuffer(VertexBuffer *_InVertexBuffer);


        void Execute() override final;
    };


    struct OpenGLBindShaderProgram : public OpenGLRenderCommand
    {
        OpenGLShader *m_Shader = nullptr;

        OpenGLBindShaderProgram(OpenGLShader *_InShader);


        void Execute() override final;
    };


    void CommandClearColorBuffer(OpenGLCommandBuffer *_InCmdBuffer, Color &_InClearColorValue);

    void CommandClearDepthStencilBuffer(OpenGLCommandBuffer *_InCmdBuffer,
                                        double _InClearDepthValue,
                                        uint32_t _InClearStencilValue);

    void CommandDraw(OpenGLCommandBuffer *_InCmdBuffer, VertexBuffer *_InVertexBuffer);

    void CommandDrawMultiples(OpenGLCommandBuffer *_InCmdBuffer, VertexBuffer *_InVertexBuffer, int32_t _InInstanceCount);

    void CommandBindVertexBuffer(OpenGLCommandBuffer *_InCmdBuffer, VertexBuffer *_InVertexBuffer);

    void CommandBindShaderProgram(OpenGLCommandBuffer *_InCmdBuffer, Shader *_InVertexBuffer);
} // namespace DadEngine::Rendering

#endif //__OPENGL_RENDER_COMMAND_HPP_