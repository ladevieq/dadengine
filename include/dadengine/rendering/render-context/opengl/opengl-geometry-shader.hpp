#ifndef __OPENGL_GEOMETRY_SHADER_HPP_
#define __OPENGL_GEOMETRY_SHADER_HPP_

#include "opengl.hpp"

#include "../../shader/shader.hpp"

namespace DadEngine
{
    class OpenGLGeometryShader : public GeometryShader
    {
        public:
        OpenGLGeometryShader(const char *_shaderCode, size_t _shaderCodeSize);

        ~OpenGLGeometryShader();


        GLuint m_shaderID = 0U;
    };
} // namespace DadEngine

#endif //!__OPENGL_GEOMETRY_SHADER_HPP_

