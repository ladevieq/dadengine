#include "OpenGLRenderCommand.hpp"

#include "OpenGLCommandBuffer.hpp"
#include "OpenGLShader.hpp"

namespace DadEngine::Rendering
{
	OpenGLBindShaderProgram::OpenGLBindShaderProgram(OpenGLShader* _InShader)
		: m_Shader(_InShader)
	{}


	void OpenGLBindShaderProgram::Execute()
	{
		OpenGLWrapper::glUseProgram(m_Shader->m_uiProgramID);
	}



	void CommandClearColorBuffer(OpenGLCommandBuffer* _InCmdBuffer, Color& _InClearColorValue)
	{
		_InCmdBuffer->m_Commands.Add(new OpenGLCommandClearColorBuffer(_InClearColorValue));
	}

	void CommandClearDepthStencilBuffer(OpenGLCommandBuffer* _InCmdBuffer, double _InClearDepthValue, uint32 _InClearStencilValue)
	{
		_InCmdBuffer->m_Commands.Add(new OpenGLCommandClearDepthStencilBuffer(_InClearDepthValue, _InClearStencilValue));
	}

	void CommandDraw(OpenGLCommandBuffer* _InCmdBuffer, VertexBuffer* _InVertexBuffer)
	{
		_InCmdBuffer->m_Commands.Add(new OpenGLCommandDraw(_InVertexBuffer));
	}

	void CommandDrawMultiples(OpenGLCommandBuffer* _InCmdBuffer, VertexBuffer* _InVertexBuffer, int32 _InInstanceCount)
	{
		_InCmdBuffer->m_Commands.Add(new OpenGLCommandDrawMultiples(_InVertexBuffer, _InInstanceCount));
	}

	void CommandBindVertexBuffer(OpenGLCommandBuffer * _InCmdBuffer, VertexBuffer * _InVertexBuffer)
	{
		_InCmdBuffer->m_Commands.Add(new OpenGLBindVertexBuffer((OpenGLVertexBuffer*)_InVertexBuffer));
	}

	void CommandBindShaderProgram(OpenGLCommandBuffer* _InCmdBuffer, Shader* _InVertexBuffer)
	{
		_InCmdBuffer->m_Commands.Add(new OpenGLBindShaderProgram((OpenGLShader*)_InVertexBuffer));
	}
}