#ifndef __OPENGL_SHADER_HPP_
#define __OPENGL_SHADER_HPP_

#include <Windows.h>
#include <gl/GL.h>

#include "../../shader/shader.hpp"

namespace DadEngine::Rendering
{
    struct VertexShader;
    struct GeometryShader;
    struct FragmentShader;

	// Object pipeline ?
	class OpenGLShader : public Shader
	{
	public:

		OpenGLShader(VertexShader *_InVertexShader, GeometryShader *_InGeometryShader, FragmentShader *_InFragmentShader);

		~OpenGLShader();


		GLuint m_uiProgramID = 0U;
	};
}

#endif //!__OPENGL_SHADER_HPP_