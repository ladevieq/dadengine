#ifndef __OPENGL_HELPER_HPP_
#define __OPENGL_HELPER_HPP_

#include <Windows.h>

#include <gl/GL.h>
#include "glext.hpp"

#include "wglext.hpp"

#include "../../Core/Core.hpp"

namespace DadEngine::Rendering::OpenGLWrapper
{
	/*
		Wrapper functions declaration
	*/
	const GLubyte* __stdcall getStringi(GLenum _InName, GLuint _InIndex);

	
	// Buffer stuff
	void __stdcall glGenBuffers(GLsizei _InBufferCount, GLuint* _InBuffers);

	void __stdcall glBindBuffer(GLenum _InTarget, GLuint _InBuffer);

	void __stdcall glBufferData(GLenum _InTarget, GLsizeiptr _InSize, const void* _InData, GLenum _InUsage);

	void __stdcall glDrawBuffers(GLsizei _InCount, GLenum* _inBuffers);

	void __stdcall glDeleteBuffers(GLsizei _InBufferCount, GLuint* _InBuffers);


	// Vertex buffer stuff
	void __stdcall glGenVertexArrays(GLsizei _InArrayCount, GLuint* _InArrays);

	void __stdcall glBindVertexArray(GLuint _InArrayIndex);

	void __stdcall glVertexAttribPointer(GLuint _InIndex, GLint _InSize, GLenum _InType, GLboolean _InNormalized, GLsizei _InStride, const void* _InPointer);

	void __stdcall glEnableVertexAttribArray(GLuint _InIndex);

	void __stdcall glDisableVertexAttribArray(GLuint _InIndex);

	void __stdcall glDeleteVertexArrays(GLsizei _InArrayCount, GLuint* _InArrays);


	// Shader stuff
	GLuint  __stdcall glCreateShader(GLenum _InShaderType);

	void  __stdcall glShaderSource(GLuint _InShaderID, GLsizei _InCount, const GLchar* const *_InShaderSource, GLint* _InLength);

	void __stdcall glCompileShader(GLuint _InShaderID);

	void __stdcall glAttachShader(GLuint _InProgramID, GLuint _InShaderID);


	void __stdcall glDetachShader(GLuint _InProgramID, GLuint _InShaderID);

	void __stdcall glGetShaderiv(GLuint _InShaderID, GLenum _InType, GLint* _OutParams);

	void __stdcall glGetShaderInfoLog(GLuint _InShaderID, GLsizei _InBufferSize, GLsizei *_InLength, GLchar *_InInfoLog);

	void __stdcall glDeleteShader(GLuint _InShaderID);


	// Shader program stuff
	GLuint __stdcall glCreateProgram();

	void __stdcall glLinkProgram(GLuint _InProgramID);

	void __stdcall glUseProgram(GLuint _InProgramID);

	void __stdcall glBindAttribLocation(GLuint _InProgramID, GLuint _InBindIndex, const char* _InBindName);

	void __stdcall glBindFragDataLocation(GLuint _InProgramID, GLuint _InBindIndex, const char* _InBindName);

	void __stdcall glGetProgramiv(GLuint _InProgramID, GLenum _InType, GLint* _OutParams);

	void __stdcall glGetProgramInfoLog(GLuint _InProgramID, GLsizei _InBufferSize, GLsizei *_InLength, GLchar *_InInfoLog);

	void __stdcall glDeleteProgram(GLuint _InProgramID);
	

	// Uniforms variable functions
	GLint __stdcall glGetUniformLocation(GLuint _InProgramID, const GLchar* _InName);

	void __stdcall glUniform4fv(GLint _InLocation, GLsizei _InCount, GLfloat* _InValues);

	void __stdcall glUniformMatrix4fv(GLint _InLocation, GLsizei _InCount, GLboolean _InTranspose, const float* _InValue);


	// Framebuffer stuff
	void __stdcall glGenFramebuffers(GLsizei _InFramebufferCount, GLuint* _InFramebuffersIndices);

	void __stdcall glBindFrameBuffer(GLenum _InType, GLuint _InFramebuffer);

	void __stdcall glDeleteFramebuffers(GLsizei _InFramebufferCount, GLuint* _InFramebuffersIndices);



#if defined(GL_EXT_vertex_array) || defined(DADOPENGLES)
	void __stdcall glDrawArrays(GLenum _InMode, GLint _InFirst, GLsizei _InCount);

	void __stdcall glDrawArrayInstanced(GLenum _InMode, GLint _InFirst, GLsizei _InCount, GLsizei _InPrimCount);
#endif

#if defined(WINDOWS)
	HGLRC _stdcall wglCreateContextAttribsARB(HDC _InHDC, HGLRC _InSharedHGLRC, const int* _InAttribList);

	#if defined(WGL_EXT_swap_control)
	BOOL __stdcall wglSwapIntervalEXT(int _InInterval);
	#endif
#endif

	void glInit();
}

#endif //!__OPENGL_HELPER_HPP_