#ifndef __OPENGL_GEOMETRY_SHADER_HPP_
#define __OPENGL_GEOMETRY_SHADER_HPP_

#include <Windows.h>
#include <gl/GL.h>

#include "../../Shader/Shader.hpp"

namespace DadEngine::Rendering
{
    class OpenGLGeometryShader : public GeometryShader
    {
        public:
        OpenGLGeometryShader(const char *_InShaderCode, size_t _InShaderCodeSize);

        ~OpenGLGeometryShader();


        GLuint m_uiShaderID = 0U;
    };
} // namespace DadEngine::Rendering

#endif //!__OPENGL_GEOMETRY_SHADER_HPP_