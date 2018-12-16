#include "OpenGLRenderCommand.hpp"

#include <Windows.h>

#include "OpenGLVertexBuffer.hpp"
#include "OpenGLCommandBuffer.hpp"
#include "OpenGLShader.hpp"
#include "../OpenGLWrapper.hpp"
#include "../../Mesh/VertexInputLayout.hpp"


namespace DadEngine::Rendering
{
    OpenGLCommandClearColorBuffer::OpenGLCommandClearColorBuffer(Color &_InClearColorValue)
        : m_ClearColor(_InClearColorValue)
    {
    }

    void OpenGLCommandClearColorBuffer::Execute()
    {
        glClearColor(m_ClearColor.r, m_ClearColor.g, m_ClearColor.b, m_ClearColor.a);
        glClear(GL_COLOR_BUFFER_BIT);
    }


    OpenGLCommandClearDepthStencilBuffer::OpenGLCommandClearDepthStencilBuffer(double _InClearDepthValue,
                                                                               uint32_t _InClearStencilValue)
        : m_ClearDepthValue(_InClearDepthValue), m_ClearStencilValue(_InClearStencilValue)
    {
    }

    void OpenGLCommandClearDepthStencilBuffer::Execute()
    {
        glClearDepth(m_ClearDepthValue);
        glClearStencil(m_ClearStencilValue);
        glClear(GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    }


    OpenGLCommandDraw::OpenGLCommandDraw(VertexBuffer *_InVertexBuffer)
        : m_VertexBuffer(_InVertexBuffer)
    {
    }

    void OpenGLCommandDraw::Execute()
    {
        OpenGLWrapper::glDrawArrays(GL_TRIANGLES, 0U, m_VertexBuffer->m_uiVertexCount);
    }


    OpenGLCommandDrawMultiples::OpenGLCommandDrawMultiples(VertexBuffer *_InVertexBuffer, int32_t _InInstanceCount)
        : m_VertexBuffer(_InVertexBuffer), m_InstanceCount(_InInstanceCount)
    {
    }

    void OpenGLCommandDrawMultiples::Execute()
    {
        OpenGLWrapper::glDrawArrayInstanced(GL_TRIANGLES, 0U, m_VertexBuffer->m_uiVertexCount, m_InstanceCount);
    }


    OpenGLBindVertexBuffer::OpenGLBindVertexBuffer(VertexBuffer *_InVertexBuffer)
        : m_VertexBuffer(_InVertexBuffer)
    {
    }

    void OpenGLBindVertexBuffer::Execute()
    {
        // Binding a VBO linked to a VAO and linking vertices inputs to the buffer
        OpenGLWrapper::glBindBuffer(GL_ARRAY_BUFFER, ((OpenGLVertexBuffer*)m_VertexBuffer)->m_uiBufferIndex);

        size_t offset = 0U;

        for (VertexInput input : m_VertexBuffer->m_verticesLayout)
        {
            uint32_t count;
            size_t size;

            input.GetInputTypeInfo(size, count);

            OpenGLWrapper::glVertexAttribPointer(input.uiIndex, count, GL_FLOAT, GL_FALSE,
                                                 (GLsizei)m_VertexBuffer->m_uiVertexLayoutStride,
                                                 (void *)offset);
            OpenGLWrapper::glEnableVertexAttribArray(input.uiIndex);

            offset += size;
        }

        // Unbinding the buffer linked to a VAO
        OpenGLWrapper::glBindBuffer(GL_ARRAY_BUFFER, 0U);

        // Bind the VAO
        OpenGLWrapper::glBindVertexArray(((OpenGLVertexBuffer *)m_VertexBuffer)->m_uiArrayIndex);
    }


    OpenGLBindShaderProgram::OpenGLBindShaderProgram(OpenGLShader *_InShader) : m_Shader(_InShader)
    {
    }

    void OpenGLBindShaderProgram::Execute()
    {
        OpenGLWrapper::glUseProgram(m_Shader->m_uiProgramID);
    }


    void CommandClearColorBuffer(OpenGLCommandBuffer *_InCmdBuffer, Color &_InClearColorValue)
    {
        _InCmdBuffer->m_Commands.Add(new OpenGLCommandClearColorBuffer(_InClearColorValue));
    }

    void CommandClearDepthStencilBuffer(OpenGLCommandBuffer *_InCmdBuffer, double _InClearDepthValue, uint32_t _InClearStencilValue)
    {
        _InCmdBuffer->m_Commands.Add(
            new OpenGLCommandClearDepthStencilBuffer(_InClearDepthValue, _InClearStencilValue));
    }

    void CommandDraw(OpenGLCommandBuffer *_InCmdBuffer, VertexBuffer *_InVertexBuffer)
    {
        _InCmdBuffer->m_Commands.Add(new OpenGLCommandDraw(_InVertexBuffer));
    }

    void CommandDrawMultiples(OpenGLCommandBuffer *_InCmdBuffer, VertexBuffer *_InVertexBuffer, int32_t _InInstanceCount)
    {
        _InCmdBuffer->m_Commands.Add(new OpenGLCommandDrawMultiples(_InVertexBuffer, _InInstanceCount));
    }

    void CommandBindVertexBuffer(OpenGLCommandBuffer *_InCmdBuffer, VertexBuffer *_InVertexBuffer)
    {
        _InCmdBuffer->m_Commands.Add(new OpenGLBindVertexBuffer((OpenGLVertexBuffer *)_InVertexBuffer));
    }

    void CommandBindShaderProgram(OpenGLCommandBuffer *_InCmdBuffer, Shader *_InVertexBuffer)
    {
        _InCmdBuffer->m_Commands.Add(new OpenGLBindShaderProgram((OpenGLShader *)_InVertexBuffer));
    }
} // namespace DadEngine::Rendering