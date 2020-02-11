#ifndef __RENDERER_HPP_
#define __RENDERER_HPP_

namespace DadEngine
{
    class Window;
    class RenderingContext;

    class Renderer
    {
        public:
        Renderer(Window *_ptrWindow);

        private:
        RenderingContext *m_ptrRenderContext = nullptr;
    };
} // namespace DadEngine

#endif // __RENDERER_HPP_

