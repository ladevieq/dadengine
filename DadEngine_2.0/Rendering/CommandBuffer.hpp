#ifndef __COMMAND_BUFFER_HPP_
#define __COMMAND_BUFFER_HPP_

#include "RenderContext/RenderContext.hpp"
#include "RenderCommand.hpp"
#include "Color.hpp"
#include "../Core/Core.hpp"

namespace DadEngine::Rendering
{
	struct CommandClear : public RenderCommand
	{
		CommandClear(const Color& _InClearColor) { m_clearColor = _InClearColor; }

		void Execute(RenderContext* _InRenderContext) override final
		{
			_InRenderContext->ClearBuffer(m_clearColor);
		}

		Color m_clearColor;
	};

	struct CommandPresent : public RenderCommand
	{
		void Execute(RenderContext* _InRenderContext) override final
		{
			_InRenderContext->Present();
		}
	};

	struct CommandBindVertexBuffer : public RenderCommand
	{
		VertexBuffer* m_vertexBuffer = nullptr;

		CommandBindVertexBuffer(VertexBuffer* _InVertexBuffer) : m_vertexBuffer(_InVertexBuffer)
		{}

		void Execute(RenderContext* _InRenderContext) override final
		{
			_InRenderContext->BindVertexBuffer(m_vertexBuffer);
		}
	};

	struct CommandBindShaderProgram : public RenderCommand
	{
		Shader* m_shader;

		CommandBindShaderProgram(Shader* _InShader)
			: m_shader(_InShader)
		{}

		void Execute(RenderContext* _InRenderContext) override final
		{
			_InRenderContext->BindShaderProgram(m_shader);
		}
	};

	struct CommandDrawVertexBuffer : public RenderCommand
	{
		VertexBuffer* m_vertexBuffer = nullptr;

		CommandDrawVertexBuffer(VertexBuffer* _InVertexBuffer) : m_vertexBuffer(_InVertexBuffer)
		{}

		void Execute(RenderContext* _InRenderContext) override final
		{
			_InRenderContext->Draw(m_vertexBuffer);
		}
	};

	struct CommandSetViewport : public RenderCommand
	{
		Viewport m_viewport;

		CommandSetViewport(Viewport& _InViewport)
			: m_viewport(_InViewport)
		{}

		void Execute(RenderContext* _InRenderContext) override final
		{
			_InRenderContext->SetViewport(m_viewport);
		}
	};

	struct CommandSetCullingMode : public RenderCommand
	{
		CullingMode m_cullingMode;

		CommandSetCullingMode(CullingMode _InCullingMode)
			: m_cullingMode(_InCullingMode)
		{}

		void Execute(RenderContext* _InRenderContext) override final
		{
			_InRenderContext->SetCullingMode(m_cullingMode);
		}
	};

	struct CommandSetFillMode : public RenderCommand
	{
		FillMode m_fillMode;

		CommandSetFillMode(FillMode _InFillMode)
			: m_fillMode(_InFillMode)
		{}

		void Execute(RenderContext* _InRenderContext) override final
		{
			_InRenderContext->SetFillMode(m_fillMode);
		}
	};


	class CommandBuffer : public RenderCommand
	{
	public:

		FORCE_INLINE virtual void BeginRecord()
		{
		}

		FORCE_INLINE virtual void EndRecord()
		{
		}

		void AddRenderCommand(RenderCommand* _InRenderCommand)
		{
			m_commands.Add(_InRenderCommand);
		}

		void Clear(const Color& _InClearColor)
		{
			m_commands.Add(new CommandClear(_InClearColor));
		}

		void Present()
		{
			m_commands.Add(new CommandPresent());
		}

		void BindVertexBuffer(VertexBuffer* _InVertexBuffer)
		{
			m_commands.Add(new CommandBindVertexBuffer(_InVertexBuffer));
		}

		void BindShaderProgram(Shader* _InShader)
		{
			m_commands.Add(new CommandBindShaderProgram(_InShader));
		}


		void DrawVertexBuffer(VertexBuffer* _InVertexBuffer)
		{
			m_commands.Add(new CommandDrawVertexBuffer(_InVertexBuffer));
		}

		void SetViewport(Viewport& _InViewport)
		{
			m_commands.Add(new CommandSetViewport(_InViewport));
		}

		void SetCullingMode(CullingMode _InCullingMode)
		{
			m_commands.Add(new CommandSetCullingMode(_InCullingMode));
		}

		void SetFillMode(FillMode _InFillMode)
		{
			m_commands.Add(new CommandSetFillMode(_InFillMode));
		}


		void Execute(RenderContext* _InRenderContext) override final
		{
			BeginRecord();

			for(RenderCommand* ptrCurrentRenderCmd: m_commands)
				ptrCurrentRenderCmd->Execute(_InRenderContext);

			EndRecord();
		}


	private:

		TArray<RenderCommand*> m_commands;
	};
}

#endif __COMMAND_BUFFER_HPP_