#ifndef __OPENGL_VERTEX_SHADER_HPP_
#define __OPENGL_VERTEX_SHADER_HPP_

#include "../../shader/shader.hpp"
#include "opengl.hpp"

namespace DadEngine
{
    class OpenGLVertexShader : public VertexShader
    {
        public:
        OpenGLVertexShader(const char *_shaderCode,
                           size_t _shaderCodeSize,
                           TArray<VertexInput> &_vertexInputLayout);


        ~OpenGLVertexShader();


        GLuint m_shaderID = 0U;
    };
} // namespace DadEngine

#endif //!__OPENGL_VERTEX_SHADER_HPP_

