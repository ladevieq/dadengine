#ifndef __RENDER_COMMAND_HPP_
#define __RENDER_COMMAND_HPP_


namespace DadEngine
{
    class RenderContext;

    struct RenderCommand
    {
        virtual void Execute(RenderContext *_renderContext) = 0;
    };
} // namespace DadEngine

#endif //__RENDER_COMMAND_HPP_

