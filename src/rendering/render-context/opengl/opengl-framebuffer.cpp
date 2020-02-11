#include "opengl-framebuffer.hpp"

#include "opengl-wrapper.hpp"

namespace DadEngine
{
    OpenGLFramebuffer::OpenGLFramebuffer()
    {
        glGenFramebuffers(1U, &m_framebufferIndex);
    }

    OpenGLFramebuffer::~OpenGLFramebuffer()
    {
        glDeleteFramebuffers(1U, &m_framebufferIndex);
    }

    void OpenGLFramebuffer::Attach(OpenGLFrmaebufferAttachment &_attachment)
    {
        // glFrame
    }
} // namespace DadEngine
