#ifndef __OPENGL_RENDER_COMMAND_HPP_
#define __OPENGL_RENDER_COMMAND_HPP_

#include <Windows.h>
#include "OpenGLVertexBuffer.hpp"

#include "../OpenGLWrapper.hpp"
#include "../../Color.hpp"

#pragma comment(lib, "OpenGL32.lib")


namespace DadEngine::Rendering
{
	class Shader;
	class OpenGLShader;
	class OpenGLCommandBuffer;


	struct OpenGLRenderCommand
	{
		virtual void Execute() = 0;
	};


	struct OpenGLCommandClearColorBuffer : public OpenGLRenderCommand
	{
		Color m_ClearColor = {};

		OpenGLCommandClearColorBuffer(Color& _InClearColorValue)
			: m_ClearColor(_InClearColorValue)
		{}

		void Execute() override final
		{
			glClearColor(m_ClearColor.r, m_ClearColor.g, m_ClearColor.b, m_ClearColor.a);
			glClear(GL_COLOR_BUFFER_BIT);
		}
	};

	struct OpenGLCommandClearDepthStencilBuffer : public OpenGLRenderCommand
	{
		double m_ClearDepthValue = 0.0;
        uint32_t m_ClearStencilValue = 0U;

		OpenGLCommandClearDepthStencilBuffer(double _InClearDepthValue, uint32_t _InClearStencilValue)
			: m_ClearDepthValue(_InClearDepthValue), m_ClearStencilValue(_InClearStencilValue)
		{}


		void Execute() override final
		{
			glClearDepth(m_ClearDepthValue);
			glClearStencil(m_ClearStencilValue);
			glClear(GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		}
	};

	struct OpenGLCommandDraw : public OpenGLRenderCommand
	{
		VertexBuffer* m_VertexBuffer = nullptr;

		OpenGLCommandDraw(VertexBuffer* _InVertexBuffer)
			: m_VertexBuffer(_InVertexBuffer)
		{}

		void Execute() override final
		{
			OpenGLWrapper::glDrawArrays(GL_TRIANGLES, 0U, m_VertexBuffer->m_uiVertexCount);
		}
	};

	struct OpenGLCommandDrawMultiples : public OpenGLRenderCommand
	{
		VertexBuffer* m_VertexBuffer = nullptr;
		int32_t m_InstanceCount = 0;

		OpenGLCommandDrawMultiples(VertexBuffer* _InVertexBuffer, int32_t _InInstanceCount)
			: m_VertexBuffer(_InVertexBuffer), m_InstanceCount(_InInstanceCount)
		{}

		void Execute() override final
		{
			OpenGLWrapper::glDrawArrayInstanced(GL_TRIANGLES, 0U, m_VertexBuffer->m_uiVertexCount, m_InstanceCount);
		}
	};

	struct OpenGLBindVertexBuffer : public OpenGLRenderCommand
	{
		OpenGLVertexBuffer* m_VertexBuffer = nullptr;

		OpenGLBindVertexBuffer(OpenGLVertexBuffer* _InVertexBuffer)
			: m_VertexBuffer(_InVertexBuffer)
		{}


		void Execute() override final
		{
			// Binding a VBO linked to a VAO and linking vertices inputs to the buffer
			OpenGLWrapper::glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer->m_uiBufferIndex);

			size_t offset = 0U;

			for (VertexInput input : m_VertexBuffer->m_verticesLayout)
			{
                uint32_t count;
				size_t size;

				input.GetInputTypeInfo(size, count);

				OpenGLWrapper::glVertexAttribPointer(input.uiIndex, count, GL_FLOAT, GL_FALSE, (GLsizei)m_VertexBuffer->m_uiVertexLayoutStride, (void*)offset);
				OpenGLWrapper::glEnableVertexAttribArray(input.uiIndex);

				offset += size;
			}

			// Unbinding the buffer linked to a VAO
			OpenGLWrapper::glBindBuffer(GL_ARRAY_BUFFER, 0U);

			// Bind the VAO
			OpenGLWrapper::glBindVertexArray(m_VertexBuffer->m_uiArrayIndex);
		}
	};


	struct OpenGLBindShaderProgram : public OpenGLRenderCommand
	{
		OpenGLShader* m_Shader = nullptr;

		OpenGLBindShaderProgram(OpenGLShader* _InShader);


		void Execute() override final;
	};



	void CommandClearColorBuffer(OpenGLCommandBuffer* _InCmdBuffer, Color& _InClearColorValue);

	void CommandClearDepthStencilBuffer(OpenGLCommandBuffer *_InCmdBuffer,
                                        double _InClearDepthValue,
                                        uint32_t _InClearStencilValue);

	void CommandDraw(OpenGLCommandBuffer* _InCmdBuffer, VertexBuffer* _InVertexBuffer);

	void CommandDrawMultiples(OpenGLCommandBuffer* _InCmdBuffer, VertexBuffer* _InVertexBuffer, int32_t _InInstanceCount);

	void CommandBindVertexBuffer(OpenGLCommandBuffer* _InCmdBuffer, VertexBuffer* _InVertexBuffer);

	void CommandBindShaderProgram(OpenGLCommandBuffer* _InCmdBuffer, Shader* _InVertexBuffer);
}

#endif //__OPENGL_RENDER_COMMAND_HPP_