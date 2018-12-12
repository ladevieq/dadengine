#ifndef __OPENGL_FRAMEBUFFER_HPP_
#define __OPENGL_FRAMEBUFFER_HPP_

namespace DadEngine::Rendering
{
	struct OpenGLFrmaebufferAttachment
	{
		AttachmentPoints m_AttachmentPoint = MAX_FRAMEBUFFER_ATTACHMENT;
	};

	class OpenGLFramebuffer : public Framebuffer
	{

	public:

		OpenGLFramebuffer()
		{
			OpenGLWrapper::glGenFramebuffers(1U, &m_uiFramebufferIndex);
		}

		~OpenGLFramebuffer()
		{
			OpenGLWrapper::glDeleteFramebuffers(1U, &m_uiFramebufferIndex);
		}


		uint32_t m_uiFramebufferIndex = 0U;

	private:

		FORCE_INLINE void Attach(OpenGLFrmaebufferAttachment& _InAttachment)
		{
			//glFrame

		}
	};
}

#endif //__OPENGL_FRAMEBUFFER_HPP_