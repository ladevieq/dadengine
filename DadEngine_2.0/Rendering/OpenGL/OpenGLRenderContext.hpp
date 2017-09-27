#ifndef __OPENGL_RENDER_CONTEXT_HPP_
#define __OPENGL_RENDER_CONTEXT_HPP_

#include "glext.hpp"
#include "wglext.hpp"

namespace DadEngine::Rendering
{
	class OpenGLRenderContext : public RenderContext
	{

	public:

		OpenGLRenderContext(PlatformWindow& _InWindow)
		{
			m_HDC = GetDC(_InWindow.GetWindowHandle());
			PIXELFORMATDESCRIPTOR pxlDescriptor = {};
			pxlDescriptor.nSize = sizeof(pxlDescriptor);
			pxlDescriptor.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
			pxlDescriptor.cColorBits = 32U;
			pxlDescriptor.cDepthBits = 24U;
			pxlDescriptor.cStencilBits = 8U;
			pxlDescriptor.iPixelType = PFD_TYPE_RGBA;
			pxlDescriptor.nVersion = 1U;

			int32 pixelFormat = ChoosePixelFormat(m_HDC, &pxlDescriptor);
			SetPixelFormat(m_HDC, pixelFormat, &pxlDescriptor);

			m_renderContext = wglCreateContext(m_HDC);
			wglMakeCurrent(m_HDC, m_renderContext);

			//uint32 uiExtensionsCount = 0U;

			//glGetIntegerv(GL_NUM_EXTENSIONS

			//for(size_t i = 0U; i < 100U; i++)
			//printf("%s\n", glGetString(GL_EXTENSIONS));

			printf("%s\n", glGetString(GL_VERSION));
			printf("%s\n", glGetString(GL_VENDOR));
			printf("%s\n", glGetString(GL_RENDERER));

			PFNGLGETSTRINGIPROC getStringi = (PFNGLGETSTRINGIPROC) wglGetProcAddress("glGetStringi");

			int32 n;

			glGetIntegerv(GL_NUM_EXTENSIONS, &n);

			for (int32 i = 0; i < n; i++)
			{
				printf("%s\n", getStringi(GL_EXTENSIONS, i));
			}

			PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");

			wglSwapIntervalEXT(0);
		}


		FORCE_INLINE void ClearBuffer(Color& _InClearColor) override final
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
			glClearColor(_InClearColor.r, _InClearColor.g, _InClearColor.b, _InClearColor.a);
		}

		FORCE_INLINE void Present() override final
		{
			SwapBuffers(m_HDC);
		}


	private:

		HDC m_HDC = nullptr; // Hardware device context one per rendering thread
		HGLRC m_renderContext = nullptr; // Hardware render context
	};
}

#endif //__OPENGL_RENDER_CONTEXT_HPP_