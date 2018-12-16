#include "OpenGLFramebuffer.hpp"

#include "../OpenGLWrapper.hpp"

namespace DadEngine::Rendering
{
    OpenGLFramebuffer::OpenGLFramebuffer()
    {
        OpenGLWrapper::glGenFramebuffers(1U, &m_uiFramebufferIndex);
    }

    OpenGLFramebuffer::~OpenGLFramebuffer()
    {
        OpenGLWrapper::glDeleteFramebuffers(1U, &m_uiFramebufferIndex);
    }

    void OpenGLFramebuffer::Attach(OpenGLFrmaebufferAttachment &_InAttachment)
    {
        // glFrame
    }
}