#ifndef __OPENGL_RENDER_CONTEXT_HPP_
#define __OPENGL_RENDER_CONTEXT_HPP_


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