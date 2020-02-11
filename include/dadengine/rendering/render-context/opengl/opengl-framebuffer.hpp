#ifndef __OPENGL_FRAMEBUFFER_HPP_
#define __OPENGL_FRAMEBUFFER_HPP_

#include "../../framebuffer.hpp"
#include "opengl.hpp"


namespace DadEngine
{
    struct OpenGLFrmaebufferAttachment
    {
        AttachmentPoints m_AttachmentPoint = MAX_FRAMEBUFFER_ATTACHMENT;
    };

    class OpenGLFramebuffer : public Framebuffer
    {

        public:
        OpenGLFramebuffer();

        ~OpenGLFramebuffer();


        GLuint m_framebufferIndex = 0U;

        private:
        void Attach(OpenGLFrmaebufferAttachment &_attachment);
    };
} // namespace DadEngine

#endif //__OPENGL_FRAMEBUFFER_HPP_

