#ifndef __COMMAND_BUFFER_HPP_
#define __COMMAND_BUFFER_HPP_

#include "RenderContext.hpp"
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


	class CommandBuffer : public RenderCommand
	{
	public:

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

		void Execute(RenderContext* _InRenderContext) override final
		{
			for(RenderCommand* ptrCurrentRenderCmd: m_commands)
				ptrCurrentRenderCmd->Execute(_InRenderContext);
		}


	private:
		TArray<RenderCommand*> m_commands;
	};
}

#endif __COMMAND_BUFFER_HPP_