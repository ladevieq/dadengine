#ifndef __OPENGL_FRAGMENT_SHADER_HPP_
#define __OPENGL_FRAGMENT_SHADER_HPP_

#include <Windows.h>
#include <gl/GL.h>

#include "../../shader/shader.hpp"

namespace DadEngine::Rendering
{
	class OpenGLFragmentShader : public FragmentShader
	{
	public:

		OpenGLFragmentShader(const char *_InShaderCode, size_t _InShaderCodeSize);

		~OpenGLFragmentShader();


		GLuint m_uiShaderID = 0U;
	};
}

#endif //!__OPENGL_FRAGMENT_SHADER_HPP_