#ifndef __OPENGL_SHADER_HPP_
#define __OPENGL_SHADER_HPP_

#include "opengl.hpp"
#include "shader/shader.hpp"

namespace DadEngine
{
    struct VertexShader;
    struct GeometryShader;
    struct FragmentShader;

    // Object pipeline ?
    class OpenGLShader : public Shader
    {
        public:
        OpenGLShader(VertexShader *_vertexShader,
                     GeometryShader *_geometryShader,
                     FragmentShader *_fragmentShader);

        virtual ~OpenGLShader();


        GLuint m_programID = 0U;
    };
} // namespace DadEngine

#endif //!__OPENGL_SHADER_HPP_

