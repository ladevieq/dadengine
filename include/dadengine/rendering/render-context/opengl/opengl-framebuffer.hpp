#ifndef __OPENGL_FRAMEBUFFER_HPP_
#define __OPENGL_FRAMEBUFFER_HPP_

#include <stdint.h>
#include "../../framebuffer.hpp"

namespace DadEngine::Rendering
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


        uint32_t m_uiFramebufferIndex = 0U;

        private:
        void Attach(OpenGLFrmaebufferAttachment &_InAttachment);

    };
} // namespace DadEngine::Rendering

#endif //__OPENGL_FRAMEBUFFER_HPP_