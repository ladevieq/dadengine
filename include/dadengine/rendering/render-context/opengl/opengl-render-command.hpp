#ifndef __OPENGL_RENDER_COMMAND_HPP_
#define __OPENGL_RENDER_COMMAND_HPP_

#include "../../color.hpp"

#include <cstdint>


namespace DadEngine
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
        Color m_clearColor = {};

        OpenGLCommandClearColorBuffer(Color &_clearColorValue);

        void Execute() override final;
    };

    struct OpenGLCommandClearDepthStencilBuffer : public OpenGLRenderCommand
    {
        double m_clearDepthValue = 0.0;
        uint32_t m_clearStencilValue = 0U;

        OpenGLCommandClearDepthStencilBuffer(double _clearDepthValue, uint32_t _clearStencilValue);


        void Execute() override final;
    };

    struct OpenGLCommandDraw : public OpenGLRenderCommand
    {
        VertexBuffer *m_vertexBuffer = nullptr;

        OpenGLCommandDraw(VertexBuffer *_vertexBuffer);

        void Execute() override final;
    };

    struct OpenGLCommandDrawMultiples : public OpenGLRenderCommand
    {
        VertexBuffer *m_vertexBuffer = nullptr;
        int32_t m_instanceCount = 0;

        OpenGLCommandDrawMultiples(VertexBuffer *_vertexBuffer, int32_t _instanceCount);

        void Execute() override final;
    };

    struct OpenGLBindVertexBuffer : public OpenGLRenderCommand
    {
        VertexBuffer *m_vertexBuffer = nullptr;

        OpenGLBindVertexBuffer(VertexBuffer *_vertexBuffer);


        void Execute() override final;
    };


    struct OpenGLBindShaderProgram : public OpenGLRenderCommand
    {
        OpenGLShader *m_shader = nullptr;

        OpenGLBindShaderProgram(OpenGLShader *_shader);


        void Execute() override final;
    };


    void CommandClearColorBuffer(OpenGLCommandBuffer *_cmdBuffer, Color &_clearColorValue);

    void CommandClearDepthStencilBuffer(OpenGLCommandBuffer *_cmdBuffer,
                                        double _clearDepthValue,
                                        uint32_t _clearStencilValue);

    void CommandDraw(OpenGLCommandBuffer *_cmdBuffer, VertexBuffer *_vertexBuffer);

    void CommandDrawMultiples(OpenGLCommandBuffer *_cmdBuffer,
                              VertexBuffer *_vertexBuffer,
                              int32_t _instanceCount);

    void CommandBindVertexBuffer(OpenGLCommandBuffer *_cmdBuffer, VertexBuffer *_vertexBuffer);

    void CommandBindShaderProgram(OpenGLCommandBuffer *_cmdBuffer, Shader *_shader);
} // namespace DadEngine

#endif //__OPENGL_RENDER_COMMAND_HPP_

