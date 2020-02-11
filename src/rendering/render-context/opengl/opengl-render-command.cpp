#include "opengl-render-command.hpp"

#include "../../mesh/vertex-input-layout.hpp"
#include "opengl-command-buffer.hpp"
#include "opengl-shader.hpp"
#include "opengl-vertex-buffer.hpp"
#include "opengl-wrapper.hpp"


namespace DadEngine
{
    OpenGLCommandClearColorBuffer::OpenGLCommandClearColorBuffer(Color &_clearColorValue)
        : m_clearColor(_clearColorValue)
    {
    }

    void OpenGLCommandClearColorBuffer::Execute()
    {
        glClearColor(m_clearColor.r, m_clearColor.g, m_clearColor.b,
                     m_clearColor.a);
        glClear(GL_COLOR_BUFFER_BIT);
    }


    OpenGLCommandClearDepthStencilBuffer::OpenGLCommandClearDepthStencilBuffer(double _clearDepthValue,
                                                                               uint32_t _clearStencilValue)
        : m_clearDepthValue(_clearDepthValue), m_clearStencilValue(_clearStencilValue)
    {
    }

    void OpenGLCommandClearDepthStencilBuffer::Execute()
    {
        glClearDepth(m_clearDepthValue);
        glClearStencil(m_clearStencilValue);
        glClear(GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    }


    OpenGLCommandDraw::OpenGLCommandDraw(VertexBuffer *_vertexBuffer)
        : m_vertexBuffer(_vertexBuffer)
    {
    }

    void OpenGLCommandDraw::Execute()
    {
        glDrawArrays(GL_TRIANGLES, 0U, m_vertexBuffer->m_vertexCount);
    }


    OpenGLCommandDrawMultiples::OpenGLCommandDrawMultiples(VertexBuffer *_vertexBuffer,
                                                           int32_t _instanceCount)
        : m_vertexBuffer(_vertexBuffer), m_instanceCount(_instanceCount)
    {
    }

    void OpenGLCommandDrawMultiples::Execute()
    {
        glDrawArrayInstanced(GL_TRIANGLES, 0U, m_vertexBuffer->m_vertexCount, m_instanceCount);
    }


    OpenGLBindVertexBuffer::OpenGLBindVertexBuffer(VertexBuffer *_vertexBuffer)
        : m_vertexBuffer(_vertexBuffer)
    {
    }

    void OpenGLBindVertexBuffer::Execute()
    {
        // Binding a VBO linked to a VAO and linking vertices inputs to the buffer
        glBindBuffer(GL_ARRAY_BUFFER,
                     dynamic_cast<OpenGLVertexBuffer *>(m_vertexBuffer)->m_bufferIndex);

        size_t offset = 0U;

        for (VertexInput input : m_vertexBuffer->m_verticesLayout)
        {
            uint32_t count;
            size_t size;

            input.GetInputTypeInfo(size, count);

            glVertexAttribPointer(input.index, count, GL_FLOAT, GL_FALSE,
                                  static_cast<GLsizei>(m_vertexBuffer->m_vertexLayoutStride),
                                  reinterpret_cast<void *>(offset));
            glEnableVertexAttribArray(input.index);

            offset += size;
        }

        // Unbinding the buffer linked to a VAO
        glBindBuffer(GL_ARRAY_BUFFER, 0U);

        // Bind the VAO
        glBindVertexArray(dynamic_cast<OpenGLVertexBuffer *>(m_vertexBuffer)->m_arrayIndex);
    }


    OpenGLBindShaderProgram::OpenGLBindShaderProgram(OpenGLShader *_shader)
        : m_shader(_shader)
    {
    }

    void OpenGLBindShaderProgram::Execute()
    {
        glUseProgram(m_shader->m_programID);
    }


    void CommandClearColorBuffer(OpenGLCommandBuffer *_cmdBuffer, Color &_clearColorValue)
    {
        _cmdBuffer->m_commands.Add(new OpenGLCommandClearColorBuffer(_clearColorValue));
    }

    void CommandClearDepthStencilBuffer(OpenGLCommandBuffer *_cmdBuffer,
                                        double _clearDepthValue,
                                        uint32_t _clearStencilValue)
    {
        _cmdBuffer->m_commands.Add(
            new OpenGLCommandClearDepthStencilBuffer(_clearDepthValue, _clearStencilValue));
    }

    void CommandDraw(OpenGLCommandBuffer *_cmdBuffer, VertexBuffer *_vertexBuffer)
    {
        _cmdBuffer->m_commands.Add(new OpenGLCommandDraw(_vertexBuffer));
    }

    void CommandDrawMultiples(OpenGLCommandBuffer *_cmdBuffer,
                              VertexBuffer *_vertexBuffer,
                              int32_t _instanceCount)
    {
        _cmdBuffer->m_commands.Add(new OpenGLCommandDrawMultiples(_vertexBuffer, _instanceCount));
    }

    void CommandBindVertexBuffer(OpenGLCommandBuffer *_cmdBuffer, VertexBuffer *_vertexBuffer)
    {
        _cmdBuffer->m_commands.Add(new OpenGLBindVertexBuffer(
            dynamic_cast<OpenGLVertexBuffer *>(_vertexBuffer)));
    }

    void CommandBindShaderProgram(OpenGLCommandBuffer *_cmdBuffer, Shader *_shader)
    {
        _cmdBuffer->m_commands.Add(
            new OpenGLBindShaderProgram(dynamic_cast<OpenGLShader *>(_shader)));
    }
} // namespace DadEngine
