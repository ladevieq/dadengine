#ifndef __OPENGL_VERTEX_SHADER_HPP_
#define __OPENGL_VERTEX_SHADER_HPP_

#include <Windows.h>
#include <gl/GL.h>
#include "../../Shader/Shader.hpp"

namespace DadEngine::Rendering
{
    class OpenGLVertexShader : public VertexShader
    {
        public:
        OpenGLVertexShader(const char *_InShaderCode, size_t _InShaderCodeSize, TArray<VertexInput> &_InVertexInputLayout);


        ~OpenGLVertexShader();


        GLuint m_uiShaderID = 0U;
    };
} // namespace DadEngine::Rendering

#endif //!__OPENGL_VERTEX_SHADER_HPP_