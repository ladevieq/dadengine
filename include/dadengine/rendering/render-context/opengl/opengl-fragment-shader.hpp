#ifndef __OPENGL_FRAGMENT_SHADER_HPP_
#define __OPENGL_FRAGMENT_SHADER_HPP_

#include "opengl.hpp"

#include "../../shader/shader.hpp"

namespace DadEngine
{
    class OpenGLFragmentShader : public FragmentShader
    {
        public:
        OpenGLFragmentShader(const char *_shaderCode, size_t _shaderCodeSize);

        ~OpenGLFragmentShader();


        GLuint m_shaderID = 0U;
    };
} // namespace DadEngine

#endif //!__OPENGL_FRAGMENT_SHADER_HPP_

