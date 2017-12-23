#ifndef __OPENGL_FRAMEBUFFER_HPP_
#define __OPENGL_FRAMEBUFFER_HPP_

namespace DadEngine::Rendering
{
	class OpenGLFramebuffer : public Framebuffer
	{
		OpenGLFramebuffer()
		{
			OpenGLWrapper::glGenFramebuffers(1U, &m_uiFramebufferIndex);
		}

		~OpenGLFramebuffer()
		{
			OpenGLWrapper::glDeleteFramebuffers(1U, &m_uiFramebufferIndex);
		}

		uint32 m_uiFramebufferIndex = 0U;
	};
}

#endif //__OPENGL_FRAMEBUFFER_HPP_